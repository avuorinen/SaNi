#include "sani/engine/services/contracts/render_service_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/messaging/messages/command_message.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/engine/services/render_service.hpp"
#include "sani/core/utils/string_utils.hpp"
#include "sani/engine/sani_engine.hpp"
#include "sani/graphics/layer.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			using namespace renderservice;

			RenderService::RenderService(engine::SaNiEngine* const engine, graphics::GraphicsDevice* const graphicsDevice) : EngineService("render service", engine),
																															 graphicsDevice(graphicsDevice),
																															 renderer(graphicsDevice) {
			}

			void RenderService::handleDocumentMessage(messages::DocumentMessage* const message) {
				const RenderServiceCommands command = static_cast<RenderServiceCommands>(message->getCommand());

				switch (command) {
				case RenderServiceCommands::GetLayers:
					getLayers(message);
					break;
				default:
					// TODO: dead letter.
					break;
				}
			}
			void RenderService::handleCommandMessage(messages::CommandMessage* const message) {
				const RenderServiceCommands command = static_cast<RenderServiceCommands>(message->getCommand());

				switch (command) {
				case RenderServiceCommands::CreateLayer:
					createLayer(message);
					break;
				case RenderServiceCommands::DeleteLayer:
					deleteLayer(message);
					break;
				default:
					// TODO: dead letter.
					break;
				}
			}

			void RenderService::createLayer(messages::CommandMessage* const message) {
				std::vector<String> tokens;

				utils::split(message->getData(), "||", tokens, true);

				SANI_ASSERT(tokens.size() == 3);
			}
			void RenderService::deleteLayer(messages::CommandMessage* const message) {
			}
			void RenderService::getLayers(messages::DocumentMessage* const message) {
			}

			void RenderService::receive(messages::Message* const message) {
				const MessageType messageType = message->getType();

				switch (messageType) {
				case MessageType::Command:
					handleCommandMessage(static_cast<messages::CommandMessage*>(message));
					break;
				case MessageType::Document:
					handleDocumentMessage(static_cast<messages::DocumentMessage*>(message));
					break;
				default:
					break;
				}
			}
			void RenderService::update(const EngineTime& time) {
			}
		}
	}
}