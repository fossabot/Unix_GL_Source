
import gtk

class app():

    def __init__(self):
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)

        self.window.set_position(gtk.WIN_POS_CENTER)
        self.window.set_title("OpenGL GLSL Controller")
        self.window.set_decorated(True)
        self.window.set_has_frame(False)
        self.window.set_resizable(False)
        self.window.set_default_size(320, 150)
        self.window.connect("destroy", gtk.main_quit)
        self.vbox = gtk.VBox()

        self.add_Controller("Shadow", 0, 50, 100, self.change_shadow)
        self.add_Controller("Opacity", 0, 50, 100, self.opacity_slider)

        self.vbox.unset_focus_chain()
        self.window.add(self.vbox)
        self.window.unset_focus_chain()
        self.window.show_all()

    def add_Controller(self, name, min, value, max, callback_func):

        hbox = gtk.HBox(spacing = 20)
        hbox.set_border_width(5)

        label = gtk.Label(name)
        label.set_alignment(xalign=0, yalign=0.7)
        label.set_can_focus(False)
        scale = gtk.HScale()
        scale.set_range(min, max)
        scale.set_value(value)
        scale.set_size_request(200, 40)
        scale.connect("value-changed", callback_func)
        scale.set_can_focus(False)

        hbox.pack_start(label, expand=True, fill=True, padding=20)
        hbox.pack_end(scale, expand=True, fill=True, padding=20)

        hbox.unset_focus_chain()
        self.vbox.pack_start(hbox, expand = True, fill=True, padding=5)


    def opacity_slider(self, w):
        self.window.set_opacity(w.get_value()/100.0 + 0.1)

    def change_shadow(self, value):
        print value.get_value()

app()
gtk.main()
