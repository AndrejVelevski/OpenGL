#pragma once

#include "Utils.h"

class Input
{
private:
	bool _a = false;
	bool _b = false;
	bool _c = false;
	bool _d = false;
	bool _e = false;
	bool _f = false;
	bool _g = false;
	bool _h = false;
	bool _i = false;
	bool _j = false;
	bool _k = false;
	bool _l = false;
	bool _m = false;
	bool _n = false;
	bool _o = false;
	bool _p = false;
	bool _q = false;
	bool _r = false;
	bool _s = false;
	bool _t = false;
	bool _u = false;
	bool _v = false;
	bool _w = false;
	bool _x = false;
	bool _y = false;
	bool _z = false;

	bool _left = false;
	bool _right = false;
	bool _up = false;
	bool _down = false;

	bool _escape = false;
	bool _space = false;
	bool _enter = false;

	bool _lshift = false;
	bool _rshift = false;
	bool _lctrl = false;
	bool _rctrl = false;
	bool _lalt = false;
	bool _ralt = false;

	double _mousex = width/2;
	double _mousey = height/2;

	bool _mouseleft = false;
	bool _mouseright = false;
	bool _mousemiddle = false;

	double _scrollx = 0;
	double _scrolly = 0;

public:
	static Input& get()
	{
		static Input instance;
		return instance;
	}

	static bool a() { return get()._a; }
	static void a(bool xx) { get()._a = xx; }
	static bool b() { return get()._b; }
	static void b(bool xx) { get()._b = xx; }
	static bool c() { return get()._c; }
	static void c(bool xx) { get()._c = xx; }
	static bool d() { return get()._d; }
	static void d(bool xx) { get()._d = xx; }
	static bool e() { return get()._e; }
	static void e(bool xx) { get()._e = xx; }
	static bool f() { return get()._f; }
	static void f(bool xx) { get()._f = xx; }
	static bool g() { return get()._g; }
	static void g(bool xx) { get()._g = xx; }
	static bool h() { return get()._h; }
	static void h(bool xx) { get()._h = xx; }
	static bool i() { return get()._i; }
	static void i(bool xx) { get()._i = xx; }
	static bool j() { return get()._j; }
	static void j(bool xx) { get()._j = xx; }
	static bool k() { return get()._k; }
	static void k(bool xx) { get()._k = xx; }
	static bool l() { return get()._l; }
	static void l(bool xx) { get()._l = xx; }
	static bool m() { return get()._m; }
	static void m(bool xx) { get()._m = xx; }
	static bool n() { return get()._n; }
	static void n(bool xx) { get()._n = xx; }
	static bool o() { return get()._o; }
	static void o(bool xx) { get()._o = xx; }
	static bool p() { return get()._p; }
	static void p(bool xx) { get()._p = xx; }
	static bool q() { return get()._q; }
	static void q(bool xx) { get()._q = xx; }
	static bool r() { return get()._r; }
	static void r(bool xx) { get()._r = xx; }
	static bool s() { return get()._s; }
	static void s(bool xx) { get()._s = xx; }
	static bool t() { return get()._t; }
	static void t(bool xx) { get()._t = xx; }
	static bool u() { return get()._u; }
	static void u(bool xx) { get()._u = xx; }
	static bool v() { return get()._v; }
	static void v(bool xx) { get()._v = xx; }
	static bool w() { return get()._w; }
	static void w(bool xx) { get()._w = xx; }
	static bool x() { return get()._x; }
	static void x(bool xx) { get()._x = xx; }
	static bool y() { return get()._y; }
	static void y(bool xx) { get()._y = xx; }
	static bool z() { return get()._z; }
	static void z(bool xx) { get()._z = xx; }

	static bool left() { return get()._left; }
	static void left(bool xx) { get()._left = xx; }
	static bool right() { return get()._right; }
	static void right(bool xx) { get()._right = xx; }
	static bool up() { return get()._up; }
	static void up(bool xx) { get()._up = xx; }
	static bool down() { return get()._down; }
	static void down(bool xx) { get()._down = xx; }

	static bool escape() { return get()._escape; }
	static void escape(bool xx) { get()._escape = xx; }
	static bool space() { return get()._space; }
	static void space(bool xx) { get()._space = xx; }
	static bool enter() { return get()._enter; }
	static void enter(bool xx) { get()._enter = xx; }

	static bool lshift() { return get()._lshift; }
	static void lshift(bool xx) { get()._lshift = xx; }
	static bool rshift() { return get()._rshift; }
	static void rshift(bool xx) { get()._rshift = xx; }
	static bool lctrl() { return  get()._lctrl; }
	static void lctrl(bool xx) {  get()._lctrl = xx; }
	static bool rctrl() { return  get()._rctrl; }
	static void rctrl(bool xx) {  get()._rctrl = xx; }
	static bool lalt() { return   get()._lalt; }
	static void lalt(bool xx) {   get()._lalt = xx; }
	static bool ralt() { return   get()._ralt; }
	static void ralt(bool xx) {   get()._ralt = xx; }

	static double mousex() { return get()._mousex; }
	static void mousex(double xx) { get()._mousex = xx; }
	static double mousey() { return get()._mousey; }
	static void mousey(double xx) { get()._mousey = xx; }

	static double scrollx() { return   get()._scrollx; }
	static void   scrollx(double xx) { get()._scrollx = xx; }
	static double scrolly() { return   get()._scrolly; }
	static void   scrolly(double xx) { get()._scrolly = xx; }

	static bool mouseleft() { return get()._mouseleft; }
	static void mouseleft(bool xx) { get()._mouseleft = xx; }
	static bool mouseright() { return get()._mouseright; }
	static void mouseright(bool xx) { get()._mouseright = xx; }
	static bool mousemiddle() { return get()._mousemiddle; }
	static void mousemiddle(bool xx) { get()._mousemiddle = xx; }
};

inline void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_A && action == GLFW_PRESS)   Input::a(true);
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) Input::a(false);
	if (key == GLFW_KEY_B && action == GLFW_PRESS)   Input::b(true);
	if (key == GLFW_KEY_B && action == GLFW_RELEASE) Input::b(false);
	if (key == GLFW_KEY_C && action == GLFW_PRESS)   Input::c(true);
	if (key == GLFW_KEY_C && action == GLFW_RELEASE) Input::c(false);
	if (key == GLFW_KEY_D && action == GLFW_PRESS)   Input::d(true);
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) Input::d(false);
	if (key == GLFW_KEY_E && action == GLFW_PRESS)   Input::e(true);
	if (key == GLFW_KEY_E && action == GLFW_RELEASE) Input::e(false);
	if (key == GLFW_KEY_F && action == GLFW_PRESS)   Input::f(true);
	if (key == GLFW_KEY_F && action == GLFW_RELEASE) Input::f(false);
	if (key == GLFW_KEY_G && action == GLFW_PRESS)   Input::g(true);
	if (key == GLFW_KEY_G && action == GLFW_RELEASE) Input::g(false);
	if (key == GLFW_KEY_H && action == GLFW_PRESS)   Input::h(true);
	if (key == GLFW_KEY_H && action == GLFW_RELEASE) Input::h(false);
	if (key == GLFW_KEY_I && action == GLFW_PRESS)   Input::i(true);
	if (key == GLFW_KEY_I && action == GLFW_RELEASE) Input::i(false);
	if (key == GLFW_KEY_J && action == GLFW_PRESS)   Input::j(true);
	if (key == GLFW_KEY_J && action == GLFW_RELEASE) Input::j(false);
	if (key == GLFW_KEY_K && action == GLFW_PRESS)   Input::k(true);
	if (key == GLFW_KEY_K && action == GLFW_RELEASE) Input::k(false);
	if (key == GLFW_KEY_L && action == GLFW_PRESS)   Input::l(true);
	if (key == GLFW_KEY_L && action == GLFW_RELEASE) Input::l(false);
	if (key == GLFW_KEY_M && action == GLFW_PRESS)   Input::m(true);
	if (key == GLFW_KEY_M && action == GLFW_RELEASE) Input::m(false);
	if (key == GLFW_KEY_N && action == GLFW_PRESS)   Input::n(true);
	if (key == GLFW_KEY_N && action == GLFW_RELEASE) Input::n(false);
	if (key == GLFW_KEY_O && action == GLFW_PRESS)   Input::o(true);
	if (key == GLFW_KEY_O && action == GLFW_RELEASE) Input::o(false);
	if (key == GLFW_KEY_P && action == GLFW_PRESS)   Input::p(true);
	if (key == GLFW_KEY_P && action == GLFW_RELEASE) Input::p(false);
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)   Input::q(true);
	if (key == GLFW_KEY_Q && action == GLFW_RELEASE) Input::q(false);
	if (key == GLFW_KEY_R && action == GLFW_PRESS)   Input::r(true);
	if (key == GLFW_KEY_R && action == GLFW_RELEASE) Input::r(false);
	if (key == GLFW_KEY_S && action == GLFW_PRESS)   Input::s(true);
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) Input::s(false);
	if (key == GLFW_KEY_T && action == GLFW_PRESS)   Input::t(true);
	if (key == GLFW_KEY_T && action == GLFW_RELEASE) Input::t(false);
	if (key == GLFW_KEY_U && action == GLFW_PRESS)   Input::u(true);
	if (key == GLFW_KEY_U && action == GLFW_RELEASE) Input::u(false);
	if (key == GLFW_KEY_V && action == GLFW_PRESS)   Input::v(true);
	if (key == GLFW_KEY_V && action == GLFW_RELEASE) Input::v(false);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)   Input::w(true);
	if (key == GLFW_KEY_W && action == GLFW_RELEASE) Input::w(false);
	if (key == GLFW_KEY_X && action == GLFW_PRESS)   Input::x(true);
	if (key == GLFW_KEY_X && action == GLFW_RELEASE) Input::x(false);
	if (key == GLFW_KEY_Y && action == GLFW_PRESS)   Input::y(true);
	if (key == GLFW_KEY_Y && action == GLFW_RELEASE) Input::y(false);
	if (key == GLFW_KEY_Z && action == GLFW_PRESS)   Input::z(true);
	if (key == GLFW_KEY_Z && action == GLFW_RELEASE) Input::z(false);

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)   Input::left(true);
	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) Input::left(false);
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)  Input::right(true);
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)  Input::right(false);
	if (key == GLFW_KEY_UP && action == GLFW_RELEASE)   Input::up(true);
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)     Input::up(false);
	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) Input::down(true);
	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) Input::down(false);

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)   Input::escape(true);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) Input::escape(false);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)    Input::space(true);
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)  Input::space(false);
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)    Input::enter(true);
	if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)  Input::enter(false);

	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)   Input::lshift(true);
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) Input::lshift(false);
	if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_PRESS)   Input::rshift(true);
	if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_RELEASE) Input::rshift(false);
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)   Input::lctrl(true);
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE) Input::lctrl(false);
	if (key == GLFW_KEY_RIGHT_CONTROL && action == GLFW_PRESS)   Input::rctrl(true);
	if (key == GLFW_KEY_RIGHT_CONTROL && action == GLFW_RELEASE) Input::rctrl(false);
	if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS)   Input::lalt(true);
	if (key == GLFW_KEY_LEFT_ALT && action == GLFW_RELEASE) Input::lalt(false);
	if (key == GLFW_KEY_RIGHT_ALT && action == GLFW_PRESS)   Input::ralt(true);
	if (key == GLFW_KEY_RIGHT_ALT && action == GLFW_RELEASE) Input::ralt(false);
}

inline void mousepos_callback(GLFWwindow* window, double xpos, double ypos)
{
	Input::mousex(xpos);
	Input::mousey(ypos);
}

inline void mousebutton_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		Input::mouseleft(true);
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		Input::mouseright(true);
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
		Input::mousemiddle(true);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		Input::mouseleft(false);
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		Input::mouseright(false);
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
		Input::mousemiddle(false);
}

inline void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Input::scrollx(xoffset);
	Input::scrolly(yoffset);
}