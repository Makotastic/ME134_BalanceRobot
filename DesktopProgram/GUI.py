import tkinter as tk
import json
import paho.mqtt.client as mqtt

# MQTT Configuration
BROKER = "127.0.0.1"
PORT = 1883
TOPIC_TILT = "TiltGains"
TOPIC_VEL = "VelGains"

# Initialize MQTT Client
client = mqtt.Client()
client.connect(BROKER, PORT, keepalive=60)

def send_tilt_gains():
    kp = float(entry_kp_tilt.get())
    ki = float(entry_ki_tilt.get())
    kd = float(entry_kd_tilt.get())
    payload = {"k_p": kp, "k_i": ki, "k_d": kd}
    client.publish(TOPIC_TILT, json.dumps(payload))
    print(f"Sent Tilt Gains: {payload}")

def send_velocity_gains():
    kp = float(entry_kp_vel.get())
    ki = float(entry_ki_vel.get())
    kd = float(entry_kd_vel.get())
    payload = {"k_p": kp, "k_i": ki, "k_d": kd}
    client.publish(TOPIC_VEL, json.dumps(payload))
    print(f"Sent Velocity Gains: {payload}")

# Create GUI Window
root = tk.Tk()
root.title("MQTT Control Panel")

# Tilt Gains Section
tk.Label(root, text="Tilt Gains").grid(row=0, column=0, columnspan=2)
tk.Label(root, text="Kp:").grid(row=1, column=0)
entry_kp_tilt = tk.Entry(root)
entry_kp_tilt.grid(row=1, column=1)

tk.Label(root, text="Ki:").grid(row=2, column=0)
entry_ki_tilt = tk.Entry(root)
entry_ki_tilt.grid(row=2, column=1)

tk.Label(root, text="Kd:").grid(row=3, column=0)
entry_kd_tilt = tk.Entry(root)
entry_kd_tilt.grid(row=3, column=1)

tk.Button(root, text="Send Tilt Gains", command=send_tilt_gains).grid(row=4, column=0, columnspan=2)

# Velocity Gains Section
tk.Label(root, text="Velocity Gains").grid(row=5, column=0, columnspan=2)
tk.Label(root, text="Kp:").grid(row=6, column=0)
entry_kp_vel = tk.Entry(root)
entry_kp_vel.grid(row=6, column=1)

tk.Label(root, text="Ki:").grid(row=7, column=0)
entry_ki_vel = tk.Entry(root)
entry_ki_vel.grid(row=7, column=1)

tk.Label(root, text="Kd:").grid(row=8, column=0)
entry_kd_vel = tk.Entry(root)
entry_kd_vel.grid(row=8, column=1)

tk.Button(root, text="Send Velocity Gains", command=send_velocity_gains).grid(row=9, column=0, columnspan=2)

# Run the GUI event loop
root.mainloop()
