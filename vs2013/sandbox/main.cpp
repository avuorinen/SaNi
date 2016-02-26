#include <iostream>
#include <locale>
#include <string>
#include <codecvt>
#include "sani/rtti/type_database.hpp"
#include "sani/rtti/object.hpp"
#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#pragma comment(lib, "OpenGL32.lib")

#include <Windows.h>

#endif
#include "sani/graphics/renderables/particle_emitter.hpp"
#include "sani/core/memory/memory.hpp"
#include "sani/engine/services/contracts/render_service_contract.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/graphics/color.hpp"
#include "sani/graphics/layer.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/window.hpp"
#include "sani/platform/graphics/viewport.hpp"
#include "sani/platform/graphics/render_target_2d.hpp"
#include "sani/debug.hpp"
#include "sani/graphics/camera2d.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/graphics/vertex_position_color.hpp"
#include "sani/core/math/vector.hpp"
#include "sani/core/func.hpp"
#include "sani/graphics/renderables/triangle.hpp"
#include "sani/graphics/renderables/triangle.hpp"
#include "sani/graphics/renderables/rectangle.hpp"
#include <random>

#include "sani/platform/file/file_system.hpp"
#include "sani/platform/file/file_stream.hpp"
#include "sani/resource/resources.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/resource/effect.hpp"
#include "sani/core/math/trigonometric.hpp"

#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/graphics/renderables/circle.hpp"

#include "sani/engine/sani_engine.hpp"

#include "sani/platform/time/engine_time.hpp"

#include "sani/engine/messaging/messages/document_message.hpp"

#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/resource/sprite_font.hpp"
#include "sani/resource/spritefont_content.hpp"
#include <xlocbuf>
#include "sani/hid/raw_input_listener.hpp"
#include "sani/rtti/serializable.hpp"
using namespace sani::resource;
using namespace sani::engine;
using namespace sani::graphics;
using namespace sani::engine::messages;
using namespace sani::engine::services::renderablemanager;
using namespace sani::engine::services::renderservice;

void initialize(SaNiEngine* const engine);

namespace sandbox {

	void update(SaNiEngine* const engine, const sani::EngineTime& time);
}

#if 1

FileSystem fileSystem;
ResourceManager* resources;
sani::hid::RawInputListener inputListener;

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include "sani/core/logging/system_console_logger.hpp"
#include "sani/platform/console.hpp"

#include "sani/core/logging/log_batcher.hpp"
#include "sani/rtti/type_info.hpp"
#include "sani/preprocessor/rtti_runtime.hpp"
#include "sani/rtti/argument.hpp"
class AATest : public sani::rtti::Serializable {
	DECLARE_SERIALIZABLE;
private:
	int kek;
	float topKek;
public:
	void setKek(int v) { kek = v; }
	int getKek() const { return kek; }
	float getTopKek() const { return topKek;  }
	AATest(int g) : kek(g), topKek(1337) {}
};

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	auto& db = sani::rtti::TypeDatabase::getInstance();
	RTTI_REGISTER_TYPE(AATest);
	sani::rtti::Type aaType({ sani::rtti::TypeInfo<AATest>::id });
	/*db.types[aaType.getID()].addField<AATest, int>("kek", [](const sani::rtti::Object& instance) {
		return instance.getValue<AATest>().getKek();
	},
	[](sani::rtti::Object& instance, const sani::rtti::Object& newValue) {
		instance.getValue<AATest>().setKek(newValue.getValue<int>());
	});*/
	RTTI_PROPERTY(AATest, kek, int, getKek, setKek);
	RTTI_READONLY_PROPERTY(AATest, topKek, float, getTopKek);
	db.types[aaType.getID()].addConstructor<AATest, int>([](sani::rtti::Arguments& args) {
		return AATest(args[0].getValue<int>());

	}, false);
	db.types[aaType.getID()].addConstructor<AATest, int>([](sani::rtti::Arguments& args) {
		return new AATest(args[0].getValue<int>());
	}, true);

	auto field = aaType.getField("kek");

	sani::rtti::Arguments args;
	int arg = 1337;
	AATest test(0);
	args.emplace_back(arg);
	{
		sani::rtti::Object obj = aaType.create(args);
		field.setValue(obj, 715517);
		test = obj.getValue<AATest>();
		auto topkek = aaType.getField("topKek");
		assert(topkek.isValid() && topkek.isReadOnly());
	}
	
	assert(test.getKek() == 715517);
	
	sani::SystemConsoleLogger logger;
	
	logger.logError("main", "is this red?");
	logger.logWarning("main", "is this yellow?");
	logger.logInfo("main", "is this green?");
	sani::console::writeLine("is this default?");

	sani::LogBatcher b;
	
	b.beginLog("WinMain", "LOG MAIN");

	b.scopeStart();
	b.logInfo("Ebin info1");
	b.logInfo("Ebin info2");
	b.logInfo("Ebin info3");

	b.scopeStart();
	b.logInfo("Some sub call");
	b.logInfo("sub prod 1");
	b.logInfo("sub prod 2");
	b.logError("dere was en error");
	b.logInfo("sub prod 3");
	b.logInfo("sub prod 4");
	b.logWarning("dere was en waanin");
	b.scopeEnd();
	
	b.scopeEnd();

//	b.endLog(logger);

	SaNiEngine engine(hInstance);
	engine.onInitialize += initialize;
	engine.onUpdate += sandbox::update;

	engine.start();
	
	return 0;
}

void createText(SpriteFont* font, const String16& text, GraphicsDevice* gd, SaNiEngine* const engine, std::vector<sani::graphics::Rectangle*>& rects) {
	float start = 400;
	float offx = start;
	float offy = 0;
	float spacing = font->lineSpacing;
	for (uint32 i = 0; i < text.size(); ++i) {
		uint32 c = static_cast<uint32>((text[i]));

		switch (c) {
		case '\r':
			continue;
		case '\n':
			offx = start;
			offy += spacing;
			continue;
		default:

			auto it = std::find_if(font->characters.begin(), font->characters.end(), [c](uint32 a) {
				return c == a;
			});


			if (it == font->characters.end()) throw std::runtime_error("asd");

			uint32 index = std::distance(font->characters.begin(), it) - 0;
			GlyphContent& glyph = font->glyphs[index];

			auto createRectangleMessage = engine->createEmptyMessage<DocumentMessage>();
			createElement(createRectangleMessage, ElementType::Rectangle);

			engine->routeMessage(createRectangleMessage);

			auto& rect = glyph.source;
			const float32 w = (float32)rect.w;
			const float32 h = (float32)rect.h;

			const float32 x = offx + glyph.xOffset;
			const float32 y = offy - glyph.yOffset + spacing; //+ font->texture->getHeight();

			sani::graphics::Rectangle* rectangle = static_cast<sani::graphics::Rectangle*>(createRectangleMessage->getData());
			NEW_DYNAMIC(sani::graphics::Rectangle, rectangle, x, y, w, h);

			rectangle->texture = font->texture;
			rectangle->fill = color::red;
			rectangle->textureSource = sani::math::Rect32f(rect.x, rect.y, rect.w, rect.h);
			recomputeVertices(*rectangle);
			setupShapeForRendering(rectangle, rectangle->borderThickness);

			rectangle->transform.origin.x = 0.0f;
			rectangle->transform.origin.y = 0.0f;

			recomputeVertices(*rectangle);
			updateRenderData(*rectangle);
			useTexturing(rectangle);

			engine->releaseMessage(createRectangleMessage);

			rects.push_back(rectangle);
			offx += glyph.xAdvance;
		}
	}
}

#include "sani/graphics/renderables/particle_emitter.hpp"
#include "sani/graphics/renderables/sprite_animator.hpp"
#include "sani/graphics/sprite_animation.hpp"
sani::graphics::ParticleEmitter* em;
sani::graphics::Circle* c;
sani::graphics::SpriteAnimator* a;

#include "sani/core/memory/memory.hpp"

void initialize(SaNiEngine* const engine) {

	auto getGraphicsDevice = engine->createEmptyMessage<messages::DocumentMessage>();
	renderservice::getGraphicsDevice(getGraphicsDevice);
	engine->routeMessage(getGraphicsDevice);

	GraphicsDevice* graphicsDevice = static_cast<GraphicsDevice*>(getGraphicsDevice->getData());
	engine->releaseMessage(getGraphicsDevice);

	resources = new ResourceManager(&fileSystem, graphicsDevice, "../../assets/");
	
	std::vector<sani::graphics::Rectangle*> rects;
	auto erkki = resources->load<Texture2D>("antrypirtu");
	auto tuksu = erkki;//resources->load<Texture2D>("tuksu");
	auto font = resources->load<SpriteFont>("font");

	for (uint32 i = 1; i < 8; i++) {
		const float32 w = 100.0f;
		const float32 h = 100.0f;

		const float32 x = i * 64.0f + w;
		const float32 y = i * 64.0f + h;
		
		auto createRectangleMessage = engine->createEmptyMessage<DocumentMessage>();
		createElement(createRectangleMessage, ElementType::Rectangle);
		
		engine->routeMessage(createRectangleMessage);

		sani::graphics::Rectangle* rectangle = static_cast<sani::graphics::Rectangle*>(createRectangleMessage->getData());
		NEW_DYNAMIC(sani::graphics::Rectangle, rectangle, x, y, w, h);

		rectangle->texture = tuksu;
		rectangle->fill = color::white;
		
		recomputeVertices(*rectangle);
		updateRenderData(*rectangle);

		engine->releaseMessage(createRectangleMessage);

		rects.push_back(rectangle);
	}

	auto createCircleMessage = engine->createEmptyMessage<DocumentMessage>();
	createElement(createCircleMessage, ElementType::Circle);

	engine->routeMessage(createCircleMessage);

	auto circle = static_cast<sani::graphics::Circle*>(createCircleMessage->getData());
	NEW_DYNAMIC(sani::graphics::Circle, circle, 400, 400, 200, 128);
	
	circle->texture = erkki;
	circle->fill = color::red;
	circle->radius = 200;

	recomputeVertices(*circle);
	updateRenderData(*circle);

	engine->releaseMessage(createCircleMessage);

	c = circle;

	auto getLayersMessage = engine->createEmptyMessage<DocumentMessage>();
	getLayers(getLayersMessage);
	engine->routeMessage(getLayersMessage);

	auto layers = static_cast<std::vector<Layer* const>*>(getLayersMessage->getData());
	auto layer = layers->operator[](0);

	layer->add(circle);

	engine->releaseMessage(getLayersMessage);
	engine->deallocateShared(layers);

	em = new ParticleEmitter(erkki, 1024);
	em->transform.position.x = 1280 / 2.0f;
	em->transform.position.y = 600;
	
	ParticleGenerator& gen = em->generator;

	gen.flags |= GeneratorFlags::VaryingVelocity;
	gen.flags |= GeneratorFlags::VaryingDecayTime;
	gen.flags |= GeneratorFlags::VaryingSpawnLocation;
	gen.flags |= GeneratorFlags::VaryingAngularVelocity;
	gen.flags |= GeneratorFlags::VaryingScale;
	gen.flags |= GeneratorFlags::UseScaleVelocity;

	gen.startVelocity = { -0.025f, -0.25f };
	gen.velocityVariance = { 0.025f, 0.25f };

	gen.baseDecayTime = 350.0f;
	gen.decayTimeVariance = 350.0f;

	gen.spawnLocationMinOffset = { -32.0f, 0.0f };
	gen.spawnLocationMaxOffset = { 32.0f, 0.0f };

	gen.baseAngularVelocity = 0.001f;
	gen.angularVelocityVariance = 0.01f;

	gen.baseScale = { 1.0f, 1.0f };
	gen.scaleVariance = { 0.5f, 0.5f };

	gen.baseScaleVelocity = { 0.001f, 0.001f };
	gen.scaleVelocityVariance = { 0.005f, 0.005f };

	gen.framesToFade = 16;
	gen.framesToFadeVariance = 4;

	initializeParticles(*em);

	a = new SpriteAnimator(
		tuksu,
		500.0f,
		500.0f,
		128.0f,
		128.0f,
		183,
		183);

	SpriteAnimation anim;
	
	SpriteAnimationFrameGroup g1(0, 3, 0);
	for (auto& frame : g1.frames) frame.holdTime = 0.25f;

	anim.frameGroups.push_back(g1);

	a->animations["a1"] = anim;

	startAnimating(*a);

	using StringConverter =
		std::wstring_convert<std::codecvt_utf8_utf16<char16>, char16, std::allocator<char16>, std::allocator<char8>>;


	StringConverter conv;
	String16 gg = conv.from_bytes(/*"\xc3\xa4\xc3\xb6\xc3\xb5\xc3\xb4\xc3\xb0"*/"dank memes w erkki?\ncompiling gentoo\nin da club\nmah datanyms");
	createText(font, gg, graphicsDevice, engine, rects);

	for (sani::graphics::Rectangle* rectangle : rects) layer->add(rectangle);

	layer->add(em);
	layer->add(a);

	inputListener.init();
}

#include "sani/core/math/trigonometric.hpp"
#include "sani/platform/time/engine_time.hpp"

// Horrible as fuck, can we get something "nicer" 
// any time soon?...
namespace sandbox {

	void update(SaNiEngine* const engine, const sani::EngineTime& time) {
		inputListener.update();
		c->transform.rotation += 0.001f;
		//c->textureSource.x = (float32)sani::math::cos(time.getTotalTime()) * 32.0f;
		//c->textureSource.y = (float32)sani::math::sin(time.getTotalTime()) * 32.0f;
		c->fill.a = 0.5f;

		recomputeVertices(*c);
		updateRenderData(*c);

		recomputeVertices(*em);
		updateRenderData(*em);
		recomputeBounds(*em);
/*
		recomputeVertices(*a);
		recomputeBounds(*a);
*/
		sani::graphics::update(*em, time);
		//sani::graphics::update(*a, time);
	}
}

#endif