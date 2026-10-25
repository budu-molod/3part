
// GRAPHIC_ELEMENTS
//
// VEC_2
// 
// GR_
// COLOR
//      -> COLOR_JOINT
// FONT
// 
// FUNCTION
// 
// FILE | for read file
//      -> VIRTUAL_INFORMATION | for taking stuff of ground
//		-> VI_CONVOIRS 
//					: CONVOIR | array
// 
// GRAPHIC_ELEMENT | gr_cord and doing with it, and virtual functions
//				   -> GR_STAT   | with char[][]
//								-> PRS_STAT
//											      : HEALTH
//												  -> PERSON
//																	: PROTECT
//												  -> CONVOIR
//                              -> GR_STAT_FILE   | with file 
//											      : FILE | сделать массив файлов? Или даже не создавать массив со всем файлом, а загружать по мере движения персонажа?
// 
//                                                -> F_GR_STAT_FILE | with format for symbols
//                                                                  -> GROUND | ground, map 
//																			  | переделать gr_this_draw на перерисовку двух символов прошлый символ и новый?
//                                                -> STUFF          | type_stuff
//                 -> GR_DIN    | with vector arr
//                              -> SELECTED_LIST  | func for move and format for selected item and primiteve item
//                                                -> MENU | menu_head
// 
//                              -> GR_USER_INFORM | for user information (of person)
//                              -> DIALOG         | for user`s form
//												  : SELECTED_LIST | yes or no
//                 -> INVENTORY | arr stuff & unit gr_draw()
//								: STUFF | array of stuff
//
// TIME | * 
// 
// VALUE | val_ & get_val_
//       -> HEALTH | status
//       -> PROTECT | protect_class



#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <ranges>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <thread>
#include <fstream>
#include <filesystem>

#define CO(x) std::cout << x
#define COE(x) CO(x << std::endl)

#define KEY_UP    72
#define KEY_DOWN  80
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_ESC   27
#define KEY_SPACE 32
#define KEY_ENTER 13
#define KEY_I 105
#define KEY_P 112

#define USER_ITEM 9

#define NAME_FOLDER_HISTORY "./History Files/"
#define NAME_FOLDER_GROUND "./Ground Files/"
#define NAME_FOLDER_INVENTARY "./Inventary Files/"
#define NAME_FOLDER_GEN "./Gen Files/"
#define POSTFIX_VIRTUAL_INFORMATION  "--virtual--information"
#define POSTFIX_CONVOIR "--convoir"
#define POSTFIX_TMP "--tmp"
#define POSTFIX_LEVEL "--level"
#define POSTFIX_TALK "--dg"
//inline std::string postfix_virtual_text = "--virtual--text";

//for game_
#define TYPE_STUFF_SIZE 5
#define WIDTH_STUFF 12
#define MAX_SIZE_INVENTORY 4

#define MAX_SIZE_WIDTH 70
#define MAX_SIZE_HEIGHT 19

// STRUCT
// VEC_2 | very importent struct for implination vector or coordinate or simple two number

struct vec_2 {
	int x;
	int y;
	vec_2(int x_val = 0, int y_val = 0);
	vec_2 operator+(const vec_2& other) const;
	vec_2 operator-(const vec_2& other) const;
	//Просто полезная операция 
	vec_2 operator*(const vec_2& other) const;
	//умножение на число
	vec_2 operator*(const int other) const;
	// скалярное умножение
	int operator^(const vec_2& other) const;
	//SIZE размер
	double operator~() const;
	vec_2 operator+=(vec_2& other);
	vec_2 operator-=(vec_2& other);
	int operator==(const vec_2& other) const;
	int operator!=(const vec_2& other) const;

	int operator>(const vec_2& other) const;
	int operator<(const vec_2& other) const;
	int operator>=(const vec_2& other) const;
	int operator<=(const vec_2& other) const;
};


namespace GR_ 
{
	
	enum color_names {
		BLACK, RED, GREEN, YELLOW,
		BLUE, PINK, BLUE_WHITE, WHITE
	};
	enum text_or_ground { TEXT, BACKGROUND };
	enum font_names { BOLD, ITALIC, UNDERLINE, STRIKETHROUGH, RESET };

	enum status { ALIVE, DEAD };
	enum protect_class { LOW, MEDIUM, HIGH };
	enum type_stuff { DIARY = 0, BLADE, HLEB, DICTIONARY, CLOTH };

// COLOR
//      -> COLOR_JOINT
// FONT

// this class COLOR give need symbols for changing color text or background

	class color {
	private:

	public:
		color_names color_name;
		text_or_ground t_o_g_name;
		color(color_names color_value = WHITE, text_or_ground t_o_g_value = TEXT);
		std::string color_char_get();
	};

	// this class COLOR_JOINT is my error ... I get problem from class COLOR, because, I tried to fix ;)

	class color_joint {
	private:

	public:
		color color_text;
		color color_background;
		color_joint(GR_::color_names color_text_value = GR_::color_names::WHITE, GR_::color_names color_background_value = GR_::color_names::BLACK);
		std::string joint_char_get();
	};

	// this class FONT give need symbols for changing font text 

	class font {
	private:

	public:
		GR_::font_names font_name;
		font(GR_::font_names font_value);
		std::string font_char_get();
	};

	inline color_joint color_for_selected(color_names::BLACK, color_names::YELLOW);
	inline color_joint color_for_items(color_names::WHITE, color_names::BLACK);

	//for ground
	inline color_joint color_of_wall = color_joint(color_names::RED, color_names::BLACK);
	inline color_joint color_of_door = color_joint(color_names::WHITE, color_names::BLUE);
	inline color_joint color_of_lift = color_joint(color_names::WHITE, color_names::GREEN);
	inline color_joint color_of_stuff = color_joint(color_names::BLACK, color_names::YELLOW);
	inline color_joint color_of_trans = color_joint(color_names::GREEN, color_names::BLUE);
	inline color_joint color_of_subject = color_joint(color_names::GREEN, color_names::YELLOW);

	inline vec_2 gr_max_inventory = { 1, 23 };
	inline vec_2 gr_max_size = { MAX_SIZE_WIDTH , MAX_SIZE_HEIGHT };
	inline vec_2 gr_max_size_2 = { 50 , MAX_SIZE_HEIGHT };

	/*inline std::vector<vec_2> ground_99 =
	{
		vec_2(1,1), vec_2(0, 1), vec_2(-1, 1),
		vec_2(1,0), vec_2(0, 0), vec_2(-1, 0),
		vec_2(1,-1), vec_2(0, -1), vec_2(-1, -1)
	};*/
	inline std::vector<vec_2> ground_99 =
	{
		vec_2(-1,-1), vec_2(0, -1), vec_2(1, -1),
		vec_2(-1,0), vec_2(0, 0), vec_2(1, 0),
		vec_2(-1,1), vec_2(0, 1), vec_2(1, 1)
	};

	
}


//FUNCTION

// FUNCTION TIME
int _is_empty_file(std::string file_name);

int wait(int time);
int wait();

char** get_c_2arr(int w, int h);
int clean_c_2arr(char** arr, int w, int h);

std::vector<std::string> str_to_arr(std::string& s_val);
std::vector<int> str_to_iarr(std::string& s_val);
std::vector<vec_2> str_to_varr(std::string& s_val);

std::string get_f_n_stuff(GR_::type_stuff t_st);
// GET NAME TYPE_STUFF
std::string get_n_stuff(GR_::type_stuff t_st);
// GET TYPE_STUFF BY NAME
int get_i_stuff(std::string s_val);

std::string get_inf_about_stuff(GR_::type_stuff t_st);

int text_draw(std::string text, GR_::color color_text);
int text_draw(std::string text, GR_::color_joint joint_value);
int head_draw(std::string text_of_head);

int char_input();
vec_2 move_for_game();
vec_2 move_for_hands();
vec_2 move_for_inv();
int move_for_menu();
int is_esc();

//clean func
int style_for_this(std::string text_with_format);
int clean_format();
int clean_all();

//cursor func
int hidde_cursor();
int show_cursor();
int is_see_cursor();
int move_on_row(int row);
int move_on_col(int col);
int move_on_start();
int move(int x, int y);
int move(vec_2 cord_val);



// FILE

// FILE | for read file
//      -> VIRTUAL_INFORMATION | for taking stuff of ground
//      -> VIRTUAL_TEXT
 
// CLASS FILE

class file 
{
protected:
	std::string file_name = "";
public:
	file(std::string name = "");
	std::string get_name_file();
	int set_name_file(std::string s_val);
};

class file_read : public file
{
protected:
	std::string file_text = "";
	//std::string file_name = "";
	int is_read = 0;
	//std::ifstream in_file;
public:
	file_read(std::string name = "");

	std::ifstream open_for_read();
	

	int close_for_read(std::ifstream& in_file);
	

	int file_update_read(std::ifstream& in_file);
	//int _clean();
	std::string file_read_();//get text of file
	
};

class file_write : public file 
{
protected:
	int is_write = 0;
public:
	file_write(std::string s_val = "");
	std::ofstream open_for_write();
	int close_for_write(std::ofstream& out_file);
	int file_write_(std::string s_val);
};

// CLASS VIRTUAL_INFORMATION
class virtual_information : public file_read
{
protected:
	std::vector < std::pair<std::string, std::string>> informs;
public:
	//std::string get_v_name(std::string name);
	int write_this();
	
	virtual_information(std::string name = "");
	int vi_fill();
	std::string get_inform(std::string s_val);
	int get_size();
	std::pair<std::string, std::string> get_item_inform(int ind);

};

//сделать ли GR_ в отдельной библиотеке? не поможет у меня получится цикл
// похоже пора переводить всё в GR_

// CLASS VI_STUFF
class vi_stuff : public virtual_information
{
protected:
	std::vector<int> vi_arr;
	file_write vi_f_write;
public:
	vi_stuff(std::string name = "");
	int get_inform(vec_2 cord_val, int booly_);
	std::vector<int> get_inform(vec_2 cord_valv = GR_::ground_99[3]);
	vec_2 get_inform(int _val);
	int write_vec_2(vec_2 cord_val, int _val);
	int _erase_();
	int _re_(std::vector<int> arr_val);

	//vec_2 item_find();

	int vi_write_tmp(vec_2 cord_val, int h_11, int _lvl_val, std::vector<int> arr_val);


};

// GRAPHIC_ELEMENT | gr_cord and doing with it, and virtual functions
//				   -> GR_STAT   | with char[][]
//                              -> GR_STAT_FILE   | with file 
//											      : FILE
// 
//                                                -> F_GR_STAT_FILE | with format for symbols
//                                                                  -> GROUND | ground, map
// 
//                                                -> STUFF          | type_stuff
// 
//                 -> GR_DIN    | with vector arr
//                              -> SELECTED_LIST  | func for move and format for selected item and primiteve item
//                                                -> MENU | menu_head
// 
//                              -> GR_USER_INFORM | for user information (of person)
//                              -> DIALOG         | for user`s form
// 
//                 -> INVENTORY | arr stuff & unit gr_draw()                     

class graphic_element {
protected:
	
	vec_2 gr_cord = { 0,0 };
	//char** gr_arr = NULL;
	
public:

	graphic_element(vec_2 cord_value);

	int set_cord(vec_2 cord_val);
	vec_2 get_cord();

	//virtual int gr_draw();
	virtual int gr_ff_out(std::string s_val = "");
};

// GR_STAT CLASS
class gr_stat : public graphic_element {

protected:

	char** gr_arr = NULL;
	int gr_width = 0, gr_height = 0;

public:

	gr_stat(vec_2 cord_value) : graphic_element(cord_value) {}

	int gr_member();
	int gr_remember(int w_val, int h_val); // увелечение или уменьшение массива

	virtual char gr_get(vec_2 cord_value);
	virtual char gr_get_(int y, int x);

	virtual int gr_s_w();
	virtual int gr_s_h();

	int gr_set(vec_2 cord_value, char c_val);
	int gr_set(int y, int x, char c_val);

	//virtual int gr_ff_out(std::string s_val);

	//virtual int gr_draw();
	// выводит вместо символа ' '
	int gr_clean();

	//~gr_stat();
};

// class GR_STAT_FILE

class gr_stat_file : public gr_stat {
protected:
	file_read gr_file_;
public:
	//file gr_for_file;
	gr_stat_file(vec_2 cord_value = { 0,0 }, std::string file_name = "");
	int gr_f_fill();
	std::string get_name_file();

	//~gr_stat_file();
};

// GR_DIN CLASS

class gr_din : public graphic_element {
protected:

	std::vector<std::string> gr_d_arr;

public:
	gr_din(vec_2 cord_value) : graphic_element(cord_value) {
		gr_d_fill();
	}
	int gr_d_add(std::string item);
	int gr_d_set(std::string item, int index);
	int gr_d_remove(int index);
	int gr_d_clean();
	// RETURN VALUE ITEM ARRAY BY INDEX
	std::string gr_d_get(int ind);
	int get_size();

	//virtual int gr_ff_out(std::string s_val);
	//virtual int gr_draw();
	virtual int gr_d_fill();

	//~gr_din();
};

// this class SELECTED_LIST for making selected list

class selected_list : public gr_din{
protected:
	GR_::color_joint joint_items, joint_selected;

	int selected_index = 0;
public:

	
	selected_list(vec_2 cord_val, 
		std::vector<std::string> items = {},
		 int index = 0, 
		GR_::color_joint items_value = GR_::color_joint(GR_::color_names::WHITE, GR_::color_names::BLACK),
		GR_::color_joint selected_value = GR_::color_joint(GR_::color_names::WHITE, GR_::color_names::BLUE));

	selected_list();

	virtual int gr_ff_out(std::string s_val);
	int select_item(int index); //set
	int selected_item_set(int index); //sum
	int get_selected_index();
	int get_select_gr();

	std::string gr_d_get();
};

class value {
protected:
	int vl_val;
public:
	value(int val);
	int vl_get();
};

class health : public value {
protected:
	//int health_value;
	GR_::status health_status;
public:
	health(int val);
	//int health_get() { return health_value; }
	int health_set(int val);
};

class protect : public value {
private:
	//int protect_value;
	GR_::protect_class protect_status;
public:
	protect(int value);
	GR_::protect_class check_protect_class(int value);

	int protect_set(int value);
};

// CLASS PRS_STAT
class prs_stat : public gr_stat
{
public:
	health health_prs;
	prs_stat(vec_2 cord_val = { 0,0 }, int health_val = 5, char c_val = 'P');
	//virtual int gr_ff_out(std::string s_val);
	int prs_fill(char c_val);
};

//CLASS PERSON
class person : public prs_stat
{
public:
	protect protect_person;
	person(vec_2 cord_val = { 0,0 }, int health_val = 5, char c_val = 'P', int protect_value = 1);
	//virtual int gr_ff_out(std::string s_val);
	//int prsn_fill();
};

// GROUND

class f_gr_stat_file :public gr_stat_file {
protected:

public:
	f_gr_stat_file(vec_2 cord_value = GR_::ground_99[4], std::string file_name = "");
	int type_symbol(char symbol); // wall or door or ' '?
	virtual int gr_ff_out(std::string s_val);
};

class ground : public f_gr_stat_file
{
protected:

	vi_stuff gr_virt_inf;

	vec_2 lie_count = { 0,0 }; // which item x, y of ground file is shown on the screen
	vec_2 lie_count_max = { 0,0 }; // max item x, y of ground file is shown on the screen

public:

	ground(vec_2 coord_value = { 0,0 }, std::string file_name = "");

	virtual int gr_s_w();
	virtual int gr_s_h();

	int turn_virt();
	int get_stuff(vec_2 cord_val);
	std::vector<int> get_stuffs();

	vec_2 get_stuff(int _val);
	vec_2 get_stuff();
	int set_stuff(person& _val,int _lvl_val, std::vector<int> arr_val);
	int set_stuff_ord(int ord);

	virtual char gr_get_(int y, int x);

	//virtual char gr_get(vec_2 cord_val);

	int set_count(vec_2 cord_val);
	int check_max_count();
	vec_2 get_s_count(vec_2 cord_val);
	vec_2 get_lie_count();

	vec_2 get_stuck(vec_2 cord_val);

	int ground_draw();
	int ground_this_draw(vec_2 _val_arr);

	vec_2 ground_door_move(vec_2 value);//обработка  события при попадание на дверь - перемещение в другую дверь строки
	vec_2 ground_lift_move(vec_2 value);//обработка  события при попадание на lift move on other lify on one raw
	int is_stop(vec_2 coordinate_value); // is wall for an answer from moving person
	int is_stop_for_(vec_2 cord_val);


};

// GAME_ELEMENTS

// VALUE | val_ & get_val_
//       -> HEALTH | status
//       -> PROTECT | protect_class
// PERSON | unit gr_stat 
//        <- GR_STAT | for gr_draw
//        : HELATH, PROTECT | values need

// STUFF <- GR_STAT_FILE | type_stuff
// INVENTORY  | arr stuff & unit gr_draw()
//           <- GRAPHIC_ELEMENTS | for gr_cord
//            : STUFF[] | is stuffs

// MENU  | 
//      <- SELECTED_LIST | menu_head()
// GR_USER_INFORM | for user information (of person)
//               <- GR_DIN | for vector arr and din draw
// DIALOG | for user`s form
//        <- GR_DIN | for gr_draw and vect arr
//        : SELECTED_LIST | for `yes` or `no`


// CLASS CONVOIR
class convoir : public prs_stat
{
protected:
	std::vector<vec_2> track;
	vec_2 step = { 0,-1 };
public:

	convoir(vec_2 cord_val = { 0,0 }, int health_val = 5, char c_val = 'C');

	int cr_set_track(std::vector<vec_2> arr_val);
	vec_2 step_on_track();
	vec_2 restep_on_track();
};

class vi_convoirs : public virtual_information 
{
protected:
	std::vector<convoir> vi_con_arr;
public:
	vi_convoirs(std::string s_val = "", char c_val = 'C');
	int vi_draw_and_check(ground& gr_, vec_2 cord_val);
	int vi_checky(vec_2 cord_val);
	int _remote(int ind);
};

class stuff : public gr_stat_file
{
protected:
	GR_::type_stuff t_st;
	GR_::font st_f;
	GR_::color_joint st_cl;
public:

	stuff(vec_2 cord_val = { 0,0 }, GR_::type_stuff st_val = GR_::DIARY) :
		gr_stat_file(cord_val, get_f_n_stuff(st_val)),
		st_f(GR_::font_names::ITALIC), st_cl(GR_::color_names::WHITE, GR_::color_names::BLACK) {
		t_st = st_val;
	}

	int set_color(GR_::color_joint joint_val);
	virtual int gr_ff_out(std::string s_val);
	GR_::type_stuff get_stuff();
};

class inventory : public graphic_element
{
protected:
	std::vector<stuff> items;
	//std::vector<int> 
	int index_selected = -1;
public:
	inventory(vec_2 cord_val = GR_::gr_max_inventory);
	virtual int gr_draw();
	int _clean();
	int inv_clean();
	int set_index_selected(int index_val);
	int get_index_selected();
	int get_size();
	// no relise while
	int add_item(int _val);
	int add_items(std::vector<int> arr_val);
	GR_::type_stuff get_item_stuff(int index);
	std::vector<int> get_items();
	int remove_item(int ind);
	int remove_items();
	//for selected index
	GR_::type_stuff get_s_stuff();
	int remove_s();
	//bool has_item(std::string item);
};
class menu : public selected_list 
{
protected:
	std::string menu_title;
	int outstep = 20;
public:
	menu(vec_2 cord_val = { 2, 2 }, std::vector<std::string>
		arr_val = { "1. Start Game\n", "2. History\n", "3. Settings\n", "4. Exit\n" },
		int ind = 0, std::string title_val = "MENU", 
			GR_::color_joint cl_val_item = GR_::color_for_items, GR_::color_joint cl_val_selec = GR_::color_for_selected);
	int menu_head();
	int menu_draw();
	int menu_clean();
};


// CLASS GR_USER_INFORM 
class gr_user_inform : public gr_din
{
protected:
public:
	virtual int gr_d_fill();
	gr_user_inform(vec_2 cord_val = vec_2(2, 0));

	int us_update_(std::string val, int index);
	int us_update_prsn(person& prsn);
	int us_update_cord(vec_2 cord_val);
	int us_update_hp(int hp);
	//virtual int gr_ff_out();
};

//CLASS DIALOG
class dialog : public gr_din 
{
protected:
	virtual_information title_stuff, _stuff;

	selected_list dg_select;
public:
	dialog(vec_2 cord_val = GR_::gr_max_size_2 + vec_2(2, 2));
	virtual int gr_d_fill();
	int dg_accept(int ind);
	int dg_accept_inform(int ind);
	// SHOW INFORMATION ABOUT STUFF
	int dg_accept_stuff(GR_::type_stuff t_st);
	int dg_set_cord(vec_2 cord_val);
};

// CLASS TALK_WINDOW
class talk_window : public menu 
{
protected:
	std::vector<std::pair<vec_2, std::vector<std::string>>> tw_arr;
public:
	talk_window(std::string file_name);
	int tw_update(vec_2 cord_val);
};

class level : public virtual_information 
{
protected:
	f_gr_stat_file file_;
	int order = -1;
	vec_2 cord_ = GR_::ground_99[0];
public:
	level(std::string file_name = "", int ord_val = 0);
	vec_2 get_place_();
	int increment();
	int _draw();
	int _set(int ind);
	int get_order();
};

namespace GR_ 
{
	//FUNCTION

	int gr_draw(gr_din& gr_val);
	int gr_draw(gr_stat& gr_val);

	int gr_these_draw(ground& _gr_, std::vector<vec_2>& _val_arr);
	int gr_this_draw(ground& _gr_, vec_2 _val_);

	int _check_it_on_gr(vec_2 it, vec_2 gr_1, vec_2 gr_2);

	std::string get_v_name(std::string name);
	std::string get_checked_name(std::string name);
	std::string get_be_name(std::string name, std::string between);
	//std::string get_checked_name(std::string name);

	std::vector<std::string> get_file_names(const std::string& folder_path, std::string cuty_, int booly_);
	std::vector<std::string> _cut_folder(std::vector<std::string>& _arr_, std::string cuty_, int booly_);

	std::string pop_(std::string s_val);
	int delete_file(std::string file_to_delete);
	int delete_file_tmp(std::string folder);

	//if booly == 1 &&, else ||
	int _booly_(int i1, int i2, int booly_);
}