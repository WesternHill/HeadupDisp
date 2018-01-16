# for kivy GUI
from kivy.config import Config
Config.set('graphics', 'width', '400')
Config.set('graphics', 'height', '300')
from kivy.properties import NumericProperty,StringProperty
from kivy.uix.label import Label
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.screenmanager import Screen
from kivy.uix.widget import Widget
from kivy.clock import Clock
from kivy.lang import Builder
from kivy.app import App

import time
import threading
import socket
import json


#
# GUI Declaration
#
Builder.load_string('''
#:kivy 1.8.0

<hud>:
    BoxLayout:
        orientation: 'vertical'
        pos: root.pos
        size: root.size

        BoxLayout:
            orientation: 'horizontal'
            Label:
                text: str('Speed')
                font_size: 30

            Label:
                text: str(root.speed)
                font_size: 120

            Label:
                text: str('kph')
                font_size: 30

        BoxLayout:
            Label:
                text: str('Engine')
                font_size: 30

            Label:
                text: str(root.eng)
                font_size: 50

            Label:
                text: str('rpm')
                font_size: 35
''')


#
# The information structure to be given for hudApp
#
class hudinfo:
    def __init__(self):
        self.speed = NumericProperty(0)
        self.eng = NumericProperty(0)
        self.gear = StringProperty("N")

    def set_speed(spd):
        self.speed = spd

    def set_eng(eng):
        self.eng = eng

    def set_gear(gear):
        self.gear = gear

# ############################
# DISPLAY FUNCTION
# ############################

class Hud(Widget):
    print("hudapp initiated")
    speed = NumericProperty(0)
    eng = NumericProperty(0)
    gear = StringProperty("N")

    def read_data(self,hudinfo):
        self.speed = hudinfo.speed
        self.eng = hudinfo.eng
        # self.gear = hudinfo.gear
        print("read_data. speed=",self.speed)


#
# ROOT of display function
#
class DispFunc(App):
    hud = Hud()

    def read_data(self,hudinfo):
        self.hud.read_data(hudinfo)

    def build(self):
        return self.hud


# ############################
#  RECEIVE DATA FUNCTION
# ############################
class RecvFunc(threading.Thread):
    # speed = NumericProperty(0)
    # eng = NumericProperty(0)
    speed = 0
    eng = 0

    def set_target(self,Hud):
        self.df = Hud

    def conn_to_server(self,ip,port):
        client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        print("client connecting to ",ip,":",port)
        client.connect((ip,port))
        print("connected.")
        return client

    def decode_data(self,recvd_data):
        dec = json.loads(frame)
        print("spd=",dec['spd'])
        print("eng=",dec['eng'])
        print("fuel-consumpt=",dec['fuel_consumpt'])

        self.speed = dec['spd']
        self.eng = dec['eng']

        # OLD IMPLEMENTATION
        # self.speed = int(recvd_data)
        # self.eng += 1

    def recv_data(self,client):
        while (1):
            res = client.recv(4096)
            self.decode_data(res)
            # self.speed += 1
            # self.eng += 1

    def apply_data(self,dt):
        hinf = hudinfo()
        hinf.speed = self.speed
        hinf.eng = self.eng

        self.df.read_data(hinf)

    def run(self):
        client = self.conn_to_server("127.0.0.1",50000)
        Clock.schedule_interval(self.apply_data,0.1)
        self.recv_data(client)



if __name__ == '__main__':
    recv_th = RecvFunc()
    recv_th.start()

    print(" separated thread")
    disp_th = DispFunc()

    recv_th.set_target(disp_th)
    disp_th.run()
