#include "sani/engine/mono/mono_include.hpp"
#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/engine/services/renderable_manager.hpp"
#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/core/memory/memory.hpp"
#include "sani/engine/mono/renderable_mono.hpp"
#include "sani/engine/mono/mono_provider.hpp"

#include <iostream>
#include <vector>

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(rectangle)

		using namespace sani::engine::services;
		using namespace sani::graphics;

		static std::vector<Rectangle*>* elements				{ nullptr };

		static Rectangle* getInstance(MonoString* instance) {
			const MonoClassDefinition classDef("SaNi.Mono.Graphics.Renderables", "Rectangle");
			MonoObject* value = MONO_PROVIDER->invoke(instance, MONO_PROVIDER->classFromDefinition(&classDef), "get_ID");

			gint32* id = (gint32*)mono_object_unbox(value);

			return elements->operator[](*id);
		}

		static MonoObject* GetTransform(MonoString* instance) {
			Rectangle* const nativeInstance = getInstance(instance);
			Transform& transform = nativeInstance->transform;

			const uint32 argc = 10;
			void* args[10];

			args[0] = &transform.position.x;
			args[1] = &transform.position.y;
			args[2] = &transform.position.z;

			args[3] = &transform.scale.x;
			args[4] = &transform.scale.y;
			args[5] = &transform.scale.z;

			args[6] = &transform.origin.x;
			args[7] = &transform.origin.y;
			args[8] = &transform.origin.z;

			args[9] = &transform.rotation;

			const MonoClassDefinition classDef("SaNi.Mono.Graphics", "Transform");

			MonoObject* monoTrasnform = MONO_PROVIDER->createObject(&classDef, args, argc);

			return monoTrasnform;
		}
		static void SetTransform(MonoString* instance, MonoObject* value) {
			// Position.
			auto px = 0.0f;
			auto py = 0.0f;
			auto pz = 0.0f;

			// Scale.
			auto sx = 0.0f;
			auto sy = 0.0f;
			auto sz = 0.0f;

			// Origin.
			auto ox = 0.0f;
			auto oy = 0.0f;
			auto oz = 0.0f;

			// Rotation.
			auto r = 0.0f;
		}

		static MonoObject* GetLocalBounds(MonoString* instance) {
			
			return nullptr;
		}
		static void SetLocalBounds(MonoString* instance, MonoObject* value) {
		}

		static MonoObject* GetGlobalBounds(MonoString* instance) {
			return nullptr;
		}

		static MonoObject* GetTextureSource(MonoString* instance) {
			return nullptr;
		}
		static void SetTextureSource(MonoString* instance, MonoObject* value) {
		}

		static MonoObject* GetTexture2D(MonoString* instance) {
			return nullptr;
		}
		static void SetTexture2D(MonoString* instance, MonoObject* value) {
		}

		static void InternalCreateRectangle(MonoString* instance, gfloat x, gfloat y, gfloat width, gfloat height, gint32* id) {
			auto* createRectangle = engine->createEmptyMessage<messages::DocumentMessage>();
			renderablemanager::createElement(createRectangle, ElementType::Rectangle);
			engine->routeMessage(createRectangle);
			
			auto* rectangle = static_cast<Rectangle*>(createRectangle->getData());
			
			NEW_DYNAMIC(Rectangle, rectangle, x, y, width, height);
			
			*id = rectangle->id;

			engine->releaseMessage(createRectangle);
		}
		static void InternalReleaseRectangle(MonoString* instance, gint32 id) {
			auto* deleteElement = engine->createEmptyMessage<messages::DocumentMessage>();
			deleteElement->setData(elements->operator[](id));

			renderablemanager::deleteElement(deleteElement, ElementType::Rectangle);
			engine->routeMessage(deleteElement);
			
			engine->releaseMessage(deleteElement);
		}

		static void getElements() {
			auto* getElements = engine->createEmptyMessage<messages::DocumentMessage>();
			renderablemanager::getElements(getElements, ElementType::Rectangle);
			engine->routeMessage(getElements);

			elements = static_cast<std::vector<Rectangle*>*>(getElements->getData());
			
			engine->releaseMessage(getElements);
		}

		bool initialize() {
			getElements();

			mono::RenderableSuperDef superDef("Rectangle", "SaNi.Mono.Graphics.Renderables");
			superDef.transform.get = GetTransform;
			superDef.transform.set = SetTransform;

			superDef.localBounds.get = GetLocalBounds;
			superDef.localBounds.set = SetLocalBounds;

			superDef.globalBounds.get = GetGlobalBounds;
			
			superDef.textureSource.get = GetTextureSource;
			superDef.textureSource.set = SetTextureSource;

			superDef.texture2D.get = GetTexture2D;
			superDef.texture2D.set = SetTexture2D;

 			mono::registerRenderableMembers(superDef);

			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, InternalCreateRectangle, InternalCreateRectangle);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, InternalReleaseRectangle, InternalReleaseRectangle);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}