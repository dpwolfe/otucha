#include "GLFWController.hpp"
#include "ModelView.hpp"
#include "AffinePoint.hpp"
#include "AffineVector.hpp"
#include "ModelViewWithShader.hpp"
#include "Block.hpp"
#include "DependencyContainer.hpp"
#include "otuchaConfig.h"
#include "Matrix3x3.hpp"
#include "TextureAtlas.hpp"
#include "TextureFont.hpp"
#include "vec.hpp"
#include "VertexBuffer.hpp"

#include <memory>
#include <iostream>

using namespace otucha;

void set3DViewingInformation(std::shared_ptr<terasca::ModelView> modelView, double xyz[6])
{
	modelView->setMCRegionOfInterest(xyz);

	rffalcon::AffinePoint eye(1.0, 1.0, 1.0);
	rffalcon::AffinePoint center(0, 0, 0);
	rffalcon::AffineVector up(0, 1, 0);

	modelView->setEyeCenterUp(eye, center, up);

	double zpp = -1.0;
	double zmin = -99.0;
	double zmax = -0.01;

	modelView->setZProjectionPlane(zpp);
	modelView->setEyeCoordinatesZMinZMax(zmin, zmax);
}

typedef struct {
	float x, y, z;
	float s, t;
	float r, g, b, a;
} Vertex;

void addText(std::shared_ptr<rffalcon::VertexBuffer> buffer, std::shared_ptr<rffalcon::TextureFont> font,
	const std::wstring &text, rffalcon::vec2 pen, const rffalcon::vec4 color)
{
	int textLength = text.length();
	for (int index = 0; index < textLength; ++index)
	{
		std::shared_ptr<rffalcon::TextureGlyph> glyph = font->getGlyph(text[index]);
		if (glyph != nullptr)
		{
			auto glyph1 = *glyph;
			float kerning = 0.0f;
			if (index > 0)
			{
				kerning = glyph->getKerning(text[index]);
			}
			pen.x += kerning;
			int x0 = static_cast<int>(pen.x + glyph->offsetX);
			int y0 = static_cast<int>(pen.y + glyph->offsetY);
			int x1 = static_cast<int>(x0 + glyph->width);
			int y1 = static_cast<int>(y0 - glyph->height);
			GLuint i[6] = { 0, 1, 2, 0, 2, 3 };
			std::shared_ptr<std::vector<GLuint>> indices = std::make_shared<std::vector<GLuint>>(i, i+6);
			Vertex v[4] = {
				{ static_cast<float>(x0), static_cast<float>(y0), 0.0f, glyph->s0, glyph->t0, color.r, color.g, color.b, color.a },
				{ static_cast<float>(x0), static_cast<float>(y1), 0.0f, glyph->s0, glyph->t1, color.r, color.g, color.b, color.a },
				{ static_cast<float>(x1), static_cast<float>(y1), 0.0f, glyph->s1, glyph->t1, color.r, color.g, color.b, color.a },
				{ static_cast<float>(x1), static_cast<float>(y0), 0.0f, glyph->s1, glyph->t0, color.r, color.g, color.b, color.a }

			};
			std::shared_ptr<std::vector<void*>> vertices = std::make_shared<std::vector<void*>>();
			vertices->push_back(&v[0]);
			vertices->push_back(&v[1]);
			vertices->push_back(&v[2]);
			vertices->push_back(&v[3]);
			buffer->push(vertices, indices);
			pen.x += glyph->advanceX;
		}
	}
}

std::shared_ptr<rffalcon::VertexBuffer> testText(const std::string &appDir)
{
	std::shared_ptr<rffalcon::TextureAtlas> atlas = std::make_shared<rffalcon::TextureAtlas>(512, 512, 3);
	rffalcon::vec2 pen = { { 5, 5 } };
	rffalcon::vec4 black = { { 0, 0, 0, 1 } };
	std::shared_ptr<rffalcon::TextureFont> font = std::make_shared<rffalcon::TextureFont>(atlas, 32.0f, appDir + "DejaVuSansMono.ttf");
	pen.x = 5;
	std::wstring text = L"#WORKSINMAIN";
	font->loadGlyphs(text);
	std::shared_ptr<rffalcon::VertexBuffer> buffer = std::make_shared<rffalcon::VertexBuffer>("vertex:3f,texCoord:2f,color:4f");
	addText(buffer, font, text, pen, black);
	
	glBindTexture(GL_TEXTURE_2D, atlas->getGLTextureId());
	return buffer;
}


int main(int argc, char* argv[])
{
	// these two lines included for Emscripten which is excluding the constructors otherwise :(
	rffalcon::Matrix4x4 matrix;
	rffalcon::Matrix3x3 matrix2;

	fprintf(stdout, "%s Version %d.%d\n", argv[0], otucha_VERSION_MAJOR, otucha_VERSION_MINOR);
	terasca::GLFWController c("otucha", terasca::Controller::DEPTH);
	c.reportVersions(std::cout);
	std::string appPath(argv[0]);
	int directoryEnd = appPath.find_last_of("/\\");
	std::string appDir = appPath.substr(0, directoryEnd + 1);
	DependencyContainer::getSingleton()->setAppDir(appDir);
	
	std::shared_ptr<terasca::ModelView> blockModelView = std::make_shared<terasca::ModelViewWithShader>(appDir + "simple.vsh", appDir + "simple.fsh");
	std::shared_ptr<rffalcon::ModelBase> blockModel = std::make_shared<rffalcon::Block>(-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f);
	blockModelView->addModel(blockModel);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	double xyz[6];
	blockModelView->getMCBoundingBox(xyz);
	set3DViewingInformation(blockModelView, xyz);

	std::shared_ptr<rffalcon::VertexBuffer> textModel = testText(appDir);
	std::shared_ptr<terasca::ModelView> textModelView = std::make_shared<terasca::ModelViewWithShader>(appDir + "v3f-t2f-c4f.vsh", appDir + "v3f-t2f-c4f.fsh");
	textModelView->addModel(textModel);
	textModelView->setProjectionType(ORTHOGRAPHIC);
	c.addModelView(textModelView);
	textModelView->getMCBoundingBox(xyz);
	set3DViewingInformation(textModelView, xyz);
	c.addModelView(blockModelView);

	// test console code to be removed later
	DependencyContainer::getSingleton()->getConsole()->registerCommand(L"test", [](warbler::t_consoleArgs_ptr args) {
		std::cout << "Console online" << std::endl;
	}, std::make_shared<warbler::t_consoleArgTypes>());
	DependencyContainer::getSingleton()->getConsole()->executeCommand(L"test");
	// end test console code

	c.run();

	return 0;
}

