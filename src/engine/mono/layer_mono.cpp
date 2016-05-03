#include "sani/engine/mono/layer_mono.hpp"

#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/messaging/messages/command_message.hpp"
#include "sani/engine/services/contracts/render_service_contract.hpp"
#include "sani/engine/services/render_service.hpp"

#include <sstream>

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(layer)

		using namespace sani::graphics;

		std::vector<MonoArray*> 

		static void Instantiate(MonoObject* instance, MonoString* name, int32 type, uint32* ptr) {
			std::stringstream ss;
			ss << mono_string_to_utf8(name);
			ss << "||";
			ss << std::to_string(type);
			ss << "||";
			ss << "0.0f";

			auto createLayer = engine->createEmptyMessage<messages::CommandMessage>();
			renderservice::createLayer(createLayer, ss.str());
			engine->routeMessage(createLayer);
		
			auto getLayers = engine->createEmptyMessage<messages::DocumentMessage>();
			renderservice::getLayers(getLayers);
			engine->routeMessage(getLayers);

			auto layers = static_cast<std::vector<graphics::Layer*>*>(getLayers->getData());
			auto layer = layers->back();

			*ptr = reinterpret_cast<IntPtr>(layer);

			engine->deallocateShared(layers);
			engine->releaseMessage(createLayer);
			engine->releaseMessage(getLayers);
		}
		static void Release(MonoObject* instance) {
			Layer* layer = getInstance<Layer>(instance);

			auto deleteLayer = engine->createEmptyMessage<messages::CommandMessage>();
			renderservice::deleteLayer(deleteLayer, layer->getName());
			engine->routeMessage(deleteLayer);

			// Release all elements.
			MONO_PROVIDER->invoke(instance, "ReleaseElements");

			engine->releaseMessage(deleteLayer);
		}

		static void GetName(MonoObject* instance, MonoString** value) {
			Layer* layer = getInstance<Layer>(instance);

			*value = MONO_PROVIDER->createString(layer->getName().c_str());
		}
		static void SetName(MonoObject* instance, MonoString* value) {
			Layer* layer = getInstance<Layer>(instance);

			layer->setName(MONO_PROVIDER->toUtf8(value));
		}
		
		static void GetOrder(MonoObject* instance, float32* value) {
			Layer* layer = getInstance<Layer>(instance);

			*value = layer->getOrder();
		}
		static void SetOrder(MonoObject* instance, float32 value) {
			Layer* layer = getInstance<Layer>(instance);
			
			layer->setOrder(value);
		}
		
		static void GetVisible(MonoObject* instance, int32* value) {
			Layer* layer = getInstance<Layer>(instance);

			*value = layer->isVisible() ? 1 : 0;
		}
		static void SetVisible(MonoObject* instance, int32 value) {
			Layer* layer = getInstance<Layer>(instance);

			if (value)	layer->show();
			else		layer->hide();
		}
		
		static void GetType(MonoObject* instance, uint8* value) {
			Layer* layer = getInstance<Layer>(instance);

			*value = static_cast<uint8>(layer->getType());
		}
		
		static void GetRenderables(MonoObject* instance, MonoArray* elements) {
			Layer* layer = getInstance<Layer>(instance);

			
		}
		
		static void Hide(MonoObject* instance) {
			Layer* layer = getInstance<Layer>(instance);
		}
		static void Show(MonoObject* instance) {
			Layer* layer = getInstance<Layer>(instance);
		}

		static void InternalAdd(MonoObject* instance) {
			Layer* layer = getInstance<Layer>(instance);
		}
		static void InternalRemove(MonoObject* instance) {
			Layer* layer = getInstance<Layer>(instance);
		}
		static void Contain(MonoObject* instance) {
			Layer* layer = getInstance<Layer>(instance);
		}

		static void Contains(MonoObject* instance) {
			Layer* layer = getInstance<Layer>(instance);
		}

		static void MoveElementsTo(MonoObject* instance) {
			Layer* layer = getInstance<Layer>(instance);
		}

		static void GetElementsCount(MonoObject* instance, int32* value) {
			Layer* layer = getInstance<Layer>(instance);

			*value = layer->elementsCount();
		}

		bool initialize() {
			return false;
		}

		MONO_MODULE_IMPL_END
	}
}