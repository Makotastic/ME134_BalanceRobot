import logging
import asyncio
from hbmqtt.broker import Broker

logger = logging.getLogger(__name__)

config = {
    'listeners': {
        'default': {
            'type': 'tcp',
            'bind': '0.0.0.0:1883',  # Standard MQTT listener
        },
        'ws-mqtt': {
            'type': 'ws',
            'bind': '127.0.0.1:8080',  # WebSocket listener on localhost:8080
            'max_connections': 10,
        },
    },
    'sys_interval': 10,
    # Removed 'auth' section for no authentication
    'topic-check': {
        'enabled': False  # Disable topic validation
    }
}

broker = Broker(config)


async def start_broker():
    await broker.start()


if __name__ == '__main__':
    formatter = "[%(asctime)s] :: %(levelname)s :: %(name)s :: %(message)s"
    logging.basicConfig(level=logging.INFO, format=formatter)
    loop = asyncio.get_event_loop()
    loop.run_until_complete(start_broker())
    loop.run_forever()