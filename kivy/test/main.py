from kivy.app import App
from kivy.uix.switch import Switch
from android import AndroidService


__version__ = '0.1'


class FlashApp(App):
    def build(self):
        self.root = Switch()
        self.service = AndroidService('Kivy FlashLight', 'I haz a FlashLight!')
        self.root.bind(active=self.toggle_flash)
        return self.root

    def toggle_flash(self, *args):
        if self.root.active:
            self.service.start()
        else:
            self.service.stop()

if __name__ == '__main__':
    FlashApp().run()