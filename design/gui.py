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

Builder.load_string('''
#:kivy 1.8.0

<hudApp>:
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
                font_size: 100

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
                font_size: 30

        BoxLayout:
            Label:
                text: str('Gear Pos')
                font_size: 30

            Label:
                text: str(root.gear)
                font_size: 50

            Label:
                text: str('')
                font_size: 30
''')


class hudApp(Widget):
    print("hudapp initiated")
    speed = NumericProperty(0)
    eng = NumericProperty(0)
    gear = StringProperty("N")

    speed_org = 0

    def update_field(self, dt):
        print("udpate_field timer")
        self.speed += 1

    def start(self):
        print("initiated timer")
        Clock.schedule_interval(self.update_field,0.5)

class TestApp(App):
    def build(self):
        happ = hudApp()
        happ.start()
        return happ

if __name__ == '__main__':
    TestApp().run()
