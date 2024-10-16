import paho.mqtt.client as mqtt
import json

# Define the MQTT settings
BROKER = "127.0.0.1"  # Public MQTT broker for testing
PORT = 1883  # Standard port for unencrypted MQTT

STARTING_GAINS = {  "k_p" : 0.5,
                    "k_i" : 0,
                    "k_d" : 0 }


# Define the callback when the client connects to the broker
def handle_connect(client, userdata, flags, reason_code, properties=None):
    print(f"Connected with reason code: {reason_code}")
    client.subscribe("StartUp")
    client.subscribe("Gains")
    client.subscribe("ErrorSum")

# Callback when a message is received from the broker
def on_message(client, userdata, msg):
    print(f"Received message: {msg.payload.decode()} on topic {msg.topic}")

    if (msg.topic == "StartUp"):
        client.publish("Gains", json.dumps(STARTING_GAINS))

# Create an MQTT client instance
client = mqtt.Client()

# Attach the callback functions
client.on_connect = handle_connect
client.on_message = on_message

# Connect to the broker
client.connect(BROKER, PORT, keepalive=60)

# Start a loop to process network events
client.loop_start()

# Keep the script running
try:
    while True:
        arr = input("Input k_p k_i k_d : ").split()
        payload = { "k_p" : int(arr[0]), "k_i" : int(arr[1]), "k_d" : int(arr[2])}
        client.publish("Gains", json.dumps(payload))
except KeyboardInterrupt:
    print("Disconnecting from broker...")
    client.disconnect()
    client.loop_stop()