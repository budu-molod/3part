#include "graphic_elements.h"

// STRUCT
// VEC_2 | very importent struct for implination vector or coordinate or simple two number

vec_2::vec_2(int x_val, int y_val) {
	this->x = x_val;
	this->y = y_val;
}
	vec_2 vec_2::operator+(const vec_2& other) const {
		return vec_2(this->x + other.x, this->y + other.y);
	}
	vec_2 vec_2::operator-(const vec_2& other) const {
		return vec_2(this->x - other.x, this->y - other.y);
	}
	//Просто полезная операция 
	vec_2 vec_2::operator*(const vec_2& other) const {
		return vec_2(this->x * other.x, this->y * other.y);
	}
	//умножение на число
	vec_2 vec_2::operator*(const int other) const {
		return vec_2(this->x * other, this->y * other);
	}
	// скалярное умножение
	int vec_2::operator^(const vec_2& other) const {
		return this->x * other.x + this->y * other.y;
	}
	//SIZE размер // надо что-то придумать, проблемно, что он возвращает (.)
	double vec_2::operator~() const {
		return std::sqrt((*this) ^ (*this));
	}
	vec_2 vec_2::operator-=(vec_2& other) {
		return vec_2(x - other.x, y - other.y);
	}
	vec_2 vec_2::operator+=(vec_2& other) {
		return vec_2(x + other.x, y + other.y);
	}
	int vec_2::operator==(const vec_2& other) const {
		if (this->x == other.x && this->y == other.y) {
			return 1;
		}
		else {
			return 0;
		}
	}
	int vec_2::operator!=(const vec_2& other) const {
		if (this->x != other.x || this->y != other.y) {
			return 1;
		}
		else {
			return 0;
		}
	}
	int vec_2::operator>(const vec_2& other) const 
	{
		if (this->x > other.x || this->y > other.y) {
			return 1;
		}
		else {
			return 0;
		}
	}
	
	int vec_2::operator<(const vec_2& other) const
	{
		if (this->x < other.x && this->y < other.y) {
			return 1;
		}
		else {

			return 0;
		}
	}
	int vec_2::operator>=(const vec_2& other) const 
	{
		if (this->x >= other.x && this->y >= other.y) {
			return 1;
		}
		else {

			return 0;
		}
	}
	int vec_2::operator<=(const vec_2& other) const 
	{
		if (this->x <= other.x && this->y <= other.y) {
			return 1;
		}
		else {

			return 0;
		}
	}

// FUNCTION

	int GR_::_booly_(int i1, int i2, int booly_) 
	{
		if (booly_) return i1 && i2;
		return i1||i2;
	}

	int GR_::delete_file(std::string file_to_delete)
	{
		try {

			if (std::filesystem::exists(file_to_delete)) {

				std::filesystem::remove(file_to_delete);
			}

		}
		catch (const std::filesystem::filesystem_error& e) {
			// Ловим системные ошибки (например, файл занят другой программой)
			std::cerr << "Критическая ошибка: " << e.what() << '\n';
		}
		return 0;
	}
	int GR_::delete_file_tmp(std::string folder) {
		std::vector<std::string> s_arr = GR_::get_file_names(folder, POSTFIX_TMP, 0);
		for (int i = 0; i < s_arr.size(); i++)
		{
			GR_::delete_file(GR_::pop_(folder + s_arr[i]));
		}
		return 0;
	}

int _is_empty_file(std::string file_name) {
	if (file_name == "" || file_name == NAME_FOLDER_GROUND || file_name == NAME_FOLDER_HISTORY) {
		return 1;
	}
	return 0;
}

std::vector<std::string> GR_::get_file_names(const std::string& folder_path, std::string cuty_, int booly_) {
	std::vector<std::string> file_names;

	try {
		// Проверяем, существует ли папка
		if (std::filesystem::exists(folder_path) && std::filesystem::is_directory(folder_path)) {

			// Проходим по всем элементам внутри папки
			for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
				// Проверяем, что это файл, а не еще одна папка
				if (std::filesystem::is_regular_file(entry.status())) {
					// entry.path().filename().string() берет только имя (например, "trajectory.txt")
					file_names.push_back(entry.path().filename().string());
				}
			}
		}
		else {
			std::cerr << "Указанный путь не существует или не является папкой!\n";
		}
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "Ошибка файловой системы: " << e.what() << '\n';
	}

	return GR_::_cut_folder(file_names, cuty_, booly_);
}
std::vector<std::string> GR_::_cut_folder(std::vector<std::string>& _arr_, std::string cuty_, int booly_)
{
	for (int i = 0; i < _arr_.size(); i++) 
	{
		if(booly_) 
		if (_arr_[i].find(cuty_) != std::string::npos) 
		{
			_arr_.erase(_arr_.begin() + i);
			i--;
		}
		else {
			_arr_[i] += "\n";
		}
		else 
		if (_arr_[i].find(cuty_) == std::string::npos) 
		{
			_arr_.erase(_arr_.begin() + i);
			i--;
		}
		else {
			_arr_[i] += "\n";
		}
	}
	return _arr_;
}
std::string GR_::get_checked_name(std::string name) 
{
	if (std::filesystem::exists(get_be_name(name,
		static_cast<std::string>(POSTFIX_TMP) + POSTFIX_VIRTUAL_INFORMATION))) 
	{
		return get_be_name(name,
			static_cast<std::string>(POSTFIX_TMP) + POSTFIX_VIRTUAL_INFORMATION);
	}
	return get_v_name(name);
}
std::string GR_::get_be_name(std::string name, std::string between) 
{
	if (name == "") return "";
	int index = name.find(".txt");
	return name.substr(0, index) +
		between + ".txt";
}
std::string GR_::get_v_name(std::string name) 
{
	return get_be_name(name, POSTFIX_VIRTUAL_INFORMATION);
}

int wait(int time) {
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
	return 0;
}
int wait() {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	return 0;
}

char** get_c_2arr(int w, int h) {
	char** arr = new char* [h];
	for (int i = 0; i < h; i++) {
		arr[i] = new char[w];
	}
	return arr;
}

int clean_c_2arr(char** arr, int h) {
	if (arr != NULL) {
		for (int i = 0; i < h; i++) {
			delete[] arr[i];
		}
		delete[] arr;
	}
	return 0;
}
int GR_::gr_draw(gr_din& gr_val)
{
	move(gr_val.get_cord().y+1, gr_val.get_cord().x+1);
	for (int i = 0; i < gr_val.get_size(); i++)
	{
		gr_val.gr_ff_out(gr_val.gr_d_get(i));
	}
	//move_on_start();
	return 0;
}
int GR_::gr_draw(gr_stat& gr_val) 
{
	//char c;
	std::string c = "";

	for (int i = gr_val.get_cord().y;
		i < gr_val.gr_s_h() + gr_val.get_cord().y; i++)
	{
		move(i + 1, gr_val.get_cord().x + 1); 

		for (int j = gr_val.get_cord().x;
			j < gr_val.gr_s_w() + gr_val.get_cord().x;
			j++)
		{
			//cursor_value.move(i + 1, j + 1);
			c = gr_val.gr_get_(i, j);
			gr_val.gr_ff_out(c);
		}
		std::cout << std::endl;
	}

	move_on_start();

	return 0;
}
int GR_::gr_these_draw(ground& _gr_, std::vector<vec_2>& _val_arr) 
{
	for (int i = 0; i < _val_arr.size(); i++)
	{
		GR_::gr_this_draw(_gr_, _val_arr[i]);
	}
	return 0;
}

int GR_::gr_this_draw(ground& _gr_, vec_2 _val_)
{

	std::string s_ = "";

	move(_val_ + vec_2(1, 1));
	s_.push_back(_gr_.gr_get(_val_));
	_gr_.gr_ff_out(s_);

	//std::cerr << s_;
	move_on_start();
	return 0;
}
int GR_::_check_it_on_gr(vec_2 it, vec_2 gr_1, vec_2 gr_2)
{
	if ((it <= gr_2) && (it >= gr_1)) 
	{
		return 1;
	}
	return 0;
}

//FUNC FOR CONVOIRS
std::vector<std::string> str_to_arr(std::string& s_val)
{
	std::vector<std::string> s_arr;

	// Разделяем строку по символу ';'
	auto parts = s_val | std::views::split(' ');

	// Перебираем кусочки и добавляем их в вектор
	for (auto&& part : parts) {
		// Конструктор std::string умеет работать с диапазонами C++20
		s_arr.push_back(std::string(part.begin(), part.end()));
	}

	return s_arr;
}
std::vector<int> str_to_iarr(std::string& s_val) 
{
	std::vector<std::string> s_arr = str_to_arr(s_val);
	std::vector<int> i_arr(s_arr.size());
	for (int i = 0; i < s_arr.size(); i++) 
	{
		i_arr[i] = std::stoi(s_arr[i]);
	}
	return i_arr;
}
std::vector<vec_2> str_to_varr(std::string& s_val) 
{
	std::vector<int> i_arr = str_to_iarr(s_val);

	if (i_arr.size() < 2) 
		return { GR_::ground_99[4] };

	std::vector<vec_2> v_arr(i_arr.size()/2);
	for (int i = 0; i < i_arr.size(); i+=2)
	{
		v_arr[i/2] = vec_2(i_arr[i],i_arr[i+1]);
	}
	return v_arr;
}

// FUNC for STUFF
std::string get_f_n_stuff(GR_::type_stuff t_st) 
{
	return NAME_FOLDER_INVENTARY + get_n_stuff(t_st) + ".txt";
}

std::string get_n_stuff(GR_::type_stuff t_st) 
{
	switch (t_st) {
	case GR_::DIARY:
		return "diary";
	case GR_::BLADE:
		return "blade";
	case GR_::HLEB:
		return "hleb";
	case GR_::DICTIONARY:
		return "dictionary";
	case GR_::CLOTH:
		return "cloth";
	default:
		return "";
	}
}

int get_i_stuff(std::string s_val) 
{
	//switch (s_val) {
	if(s_val ==  "diary")
		return 0;
	if (s_val == "blade")
		return 1;
	if (s_val == "hleb")
		return 2;
	if (s_val == "dictionary")
		return 3;
	if (s_val == "cloth")
		return 4;
	return -1;
	//}
}


// TEXT FUNC 
int text_draw(std::string text, GR_::color color_text) {
	std::cout << color_text.color_char_get() + text; clean_format();
	return 0;
}
int text_draw(std::string text, GR_::color_joint joint_value) {
	style_for_this(joint_value.joint_char_get() + text);
	return 0;
}


/*int graphic::person_draw(person person_for_draw) {
	move_on_col(person_for_draw.coordinate_of_person.x); move_on_row(person_for_draw.coordinate_of_person.y); std::cout << "P";
	//std::this_thread::sleep_for(std::chrono::seconds(10));
	return 0;
*/
int head_draw(std::string text_of_head) {
	move_on_col(20);
	std::cout << GR_::font(GR_::font_names::BOLD).font_char_get() <<
		GR_::color(GR_::color_names::RED, GR_::text_or_ground::TEXT).color_char_get() <<
		text_of_head << GR_::font(GR_::font_names::RESET).font_char_get() << std::endl;
	return 0;
}

int char_input() {
	int ch = _getch();
	if (ch == 0 || ch == 224) ch = _getch();
	return ch;
}

vec_2 move_for_game() {
	//start of axic is left up angl
	int c = char_input();
	switch (c) {
	case KEY_LEFT://left
		return vec_2(-1, 0);
		break;
	case KEY_UP://up
		return vec_2(0, -1);
		break;
	case KEY_RIGHT://right
		return vec_2(1, 0);
		break;
	case KEY_DOWN://down
		return vec_2(0, 1);
		break;
	case KEY_ESC://esc
		return vec_2(2, 7);
		break;
	case KEY_ENTER:
		return vec_2(1, 3);
		break;
	case 'i':// inventory
		return vec_2(10, 5);
		break;
	case 'p'://person
		return vec_2(11, 2);
		break;
	default:
		return vec_2(0, 0);
		break;
	}
}

vec_2 move_for_hands() {
	//start of axic is left up angl
	int c = char_input();
	switch (c) {
	case KEY_LEFT://left
		return vec_2(-1, 0);
		break;
	case KEY_UP://up
		return vec_2(0, -1);
		break;
	case KEY_RIGHT://right
		return vec_2(1, 0);
		break;
	case KEY_DOWN://down
		return vec_2(0, 1);
		break;
	default:
		return vec_2(0, 0);
		break;
	}

}
vec_2 move_for_inv() {
	//start of axic is left up angl
	int c = char_input();
	switch (c) {
	case KEY_LEFT://left
		return vec_2(-1, 0);
		break;
	case KEY_UP://up
		return vec_2(0, -1);
		break;
	case KEY_RIGHT://right
		return vec_2(1, 0);
		break;
	case KEY_DOWN://down
		return vec_2(0, 1);
		break;
	case KEY_ENTER:
		return vec_2(1, 3);
		break;
	default:
		return vec_2(0, 0);
		break;
	}

}


int move_for_menu() {
	int c = char_input();
	switch (c) {
	case KEY_UP://up
		return -1;
		break;
	case KEY_DOWN://down
		return 1;
		break;
	case KEY_ENTER:
		return -2;
		break;
	default:
		return 0;
		break;
	}


}
int is_esc() {
	int c = char_input();
	switch (c) {
	case KEY_ESC://esc
		return 1;
		break;
	default:
		return 0;
		break;
	}
}

// class cursor

int hidde_cursor() {
	std::cout << "\033[?25l";
	return 0;
}
int show_cursor() {
	std::cout << "\033[?25h";
	return 0;
}
int move_on_row(int row) {
	std::cout << "\033[" << row << "B"; //Вниз на N строк:
	return 0;
}
int move_on_col(int col) {
	if (col == 0) return 0;//Вправо на N столбцов
	std::cout << "\033[" << col << "C";
	return 0;
}
int move_on_start() {
	std::cout << "\033[1;1H";
	return 0;
}
//if you intersed x and y removed
int move(int x, int y)
{
	std::cout << "\033[" << x << ";" << y << "H";
	return 0;
}
int move(vec_2 cord_val)
{
	move(cord_val.y, cord_val.x);
	return 0;
}

// clean func


int clean_format() {
	std::cout << GR_::font(GR_::font_names::RESET).font_char_get();
	return 0;
}
int clean_all() {
	std::cout << "\033[2J\033[H";
	return 0;
}
//output text after clean format
int style_for_this(std::string text_with_format) {
	std::cout << text_with_format;
	clean_format();
	return 0;
}


//class color

GR_::color::color(GR_::color_names color_value, GR_::text_or_ground t_o_g_value) {
	color_name = color_value;
	t_o_g_name = t_o_g_value;
}

std::string GR_::color::color_char_get() {
	switch (color_name) {
	case GR_::color_names::BLACK:
		if (t_o_g_name == GR_::text_or_ground::TEXT) return "\033[30m";
		else return "\033[40m";
		break;
	case GR_::color_names::RED:
		if (t_o_g_name == GR_::text_or_ground::TEXT) return "\033[31m";
		else return "\033[41m";
		break;
	case GR_::color_names::GREEN:
		if (t_o_g_name == GR_::text_or_ground::TEXT) return "\033[32m";
		else return "\033[42m";
		break;
	case GR_::color_names::YELLOW:
		if (t_o_g_name == GR_::text_or_ground::TEXT) return "\033[33m";
		else return "\033[43m";
		break;
	case GR_::color_names::BLUE:
		if (t_o_g_name == GR_::text_or_ground::TEXT) return "\033[34m";
		else return "\033[44m";
		break;
	case GR_::color_names::PINK:
		if (t_o_g_name == GR_::text_or_ground::TEXT) return "\033[35m";
		else return "\033[41m";
		break;
	case GR_::color_names::BLUE_WHITE:
		if (t_o_g_name == GR_::text_or_ground::TEXT) return "\033[36m";
		else return "\033[44m";
		break;
	case GR_::color_names::WHITE:
		if (t_o_g_name == GR_::text_or_ground::TEXT) return "\033[37m";
		else return "\033[44m";
		break;
	}
}

// class color_joint

GR_::color_joint::color_joint(color_names color_text_value, color_names color_background_value) {
	color_text = color(color_text_value, GR_::text_or_ground::TEXT);
	color_background = color(color_background_value, GR_::text_or_ground::BACKGROUND);
}

std::string GR_::color_joint::joint_char_get() {
	return color_text.color_char_get() + color_background.color_char_get();
}


// class font

GR_::font::font(GR_::font_names font_value) {
	font_name = font_value;
}
std::string GR_::font::font_char_get() {
	switch (font_name) {
	case BOLD:
		return "\033[1m";
		break;
	case ITALIC:
		return "\033[3m";
		break;
	case UNDERLINE:
		return "\033[4m";
		break;
	case STRIKETHROUGH:
		return "\033[9m";
		break;
	case RESET:
		return "\033[0m";
		break;
	}
}

//remove last symbol
std::string GR_::pop_(std::string s_val)
{
	if (!s_val.empty())
		s_val.pop_back();
	return s_val;
}

// CLASS FILE

file::file(std::string name) {
	file_name = name;
	//is_read = 0;
}
std::string file::get_name_file()
{
	return file_name;
}
int file::set_name_file(std::string s_val) 
{
	file_name = s_val;
	return 0;
}

// CLASS FILE_READ
file_read::file_read(std:: string s_val) : file(s_val){}

std::ifstream file_read::open_for_read() {

	std::ifstream in_file = std::ifstream(file_name);

	if (!in_file.is_open()) {
		std::cerr << "Error of file, file isn`t found" << std::endl;
	}
	is_read = -1;
	return in_file;
}

int file_read::close_for_read(std::ifstream& in_file)
{
	if (is_read == -1)
	{
		in_file.close();
		is_read = 0;
	}
	return 0;
}

//CLASS WRITE
std::ofstream file_write::open_for_write() 
{

	std::ofstream out_file = std::ofstream(file_name, std::ios::trunc);

	if (!out_file.is_open()) 
	{
		std::cerr << "Error of file, file isn`t found" << std::endl;
	}

	is_write = -1;
	return out_file;
}

int file_write::close_for_write(std::ofstream& out_file) 
{
	if (is_write == -1) {
		out_file.close();
		is_write = 0;
	}
	return 0;
}
file_write::file_write(std::string s_val) : file(s_val)
{}
int file_write::file_write_(std::string s_val) 
{
	std::ofstream out_file = open_for_write();
	out_file << s_val;
	close_for_write(out_file);
	//is_write = 
	return 0;
}
int file_read::file_update_read(std::ifstream& in_file) {
	std::string value = "";

	file_text = "";

	while (std::getline(in_file, value)) {
		file_text += value + "\n";
		value = "";
	}
	return 0;
}

std::string file_read::file_read_() {
	if (is_read == 0) {
		std::ifstream in_file = open_for_read();
		if (in_file.is_open()) {
			file_update_read(in_file);
			close_for_read(in_file);
			is_read = 1;
		}
	}
	return file_text;
}

//CLASS FILE_WRITE



// class VIRTUAL_INFORMATION


virtual_information::virtual_information(std::string name) :
	file_read(name)
{
	std::string s_val = GR_::get_checked_name(file_name);
	set_name_file(s_val);
	
	vi_fill();
}

int virtual_information::vi_fill() 
{
	if (file_name == "") return 0;

	std::ifstream in_file = open_for_read();
	if (!in_file.is_open()) {
		std::cerr << "ERROR";
		return 0;
	}
	std::string title_val, _val;
	while (std::getline(in_file, title_val))
	{
		std::getline(in_file, _val);
		informs.push_back({ title_val, _val });
	}
	close_for_read(in_file);
	return 0;
}

int virtual_information::write_this() 
{
	file_text = "";
	for (int i = 0; i < this->informs.size(); i++) 
	{
		file_text += informs[i].first + "\n" + informs[i].second + "\n";
	}
	return 0;
}

std::string virtual_information::get_inform(std::string s_val) 
{
	for (int i = 0; i < informs.size(); i++) 
	{
		if (informs[i].first == s_val) 
		{
			return informs[i].second;
		}
	}
	return POSTFIX_VIRTUAL_INFORMATION;
}
int virtual_information::get_size() 
{
	return static_cast<int>(informs.size());
}

std::pair<std::string, std::string> virtual_information::get_item_inform(int ind) 
{
	return this->informs[ind];
}

// CLASS VI_STUFF
vi_stuff::vi_stuff(std::string name) :
	virtual_information(name)
{

	vi_f_write.set_name_file(GR_::get_v_name(GR_::get_be_name(name, static_cast<std::string>(POSTFIX_TMP))));

	for (int i = 0; i < informs.size()/3; i ++) {
		vi_arr.push_back(0);
	}
}

int vi_stuff::write_vec_2(vec_2 cord_val, int _val)
{
	// IT IS BAD!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	for (int i = 0; i < vi_arr.size(); i++)
	{
		if (informs[i * 3 + 2].second == std::to_string(_val)) 
		{
			informs[i*3].second = std::to_string(cord_val.x);
			informs[i * 3 + 1].second = std::to_string(cord_val.y);
			//return 0;
		}
	}
	return 0;
}

int vi_stuff::_erase_()
{
	for(int i = 0; i < vi_arr.size(); i ++)
	if (vi_arr[i] == 1)
	{
		informs.erase(informs.begin() + i * 3, informs.begin() + i * 3 + 3);
		vi_arr.erase(vi_arr.begin() + i);
		i--;
	}
	return 0;
}

int vi_stuff::_re_(std::vector<int> arr_val)
{
	for (int i = 0; i < arr_val.size(); i++)
	{
		informs.push_back({ "x", "-1" });
		informs.push_back({ "y", "0" });
		informs.push_back({ "S", std::to_string(arr_val[i])});
		//.push_back(GR_::ground_99[3], arr_val[i]);
	}

	return 0;
}

int vi_stuff::vi_write_tmp(vec_2 cord_val , int h_11, int _lvl_val, std::vector<int> arr_val)
{
	write_vec_2(cord_val, 27);
	write_vec_2(GR_::ground_99[5] * _lvl_val, 151);
	write_vec_2(GR_::ground_99[5] * h_11, 11);

	_erase_();

	_re_(arr_val);

	write_this();
	vi_f_write.file_write_(file_text);
	return 0;
}

int vi_stuff::get_inform(vec_2 cord_val, int booly_) 
{
	int i1;
	for (int i = 0; i < vi_arr.size(); i++) {
		i1 = informs[i * 3].second == std::to_string(cord_val.x) && informs[i * 3 + 1].second == std::to_string(cord_val.y);
		if (GR_::_booly_ (i1, vi_arr[i] == 0, booly_) && i1) 
		{
			if(booly_)vi_arr[i] = 1;
			return std::stoi(informs[i*3+2].second);
		}
	}
	return -1;
}
std::vector<int> vi_stuff::get_inform(vec_2 cord_val)
{
	std::vector<int> arr_val = {};
	for (int i = 0; i < vi_arr.size(); i++)
	{
		if (informs[i * 3].second == std::to_string(cord_val.x) && informs[i * 3 + 1].second == std::to_string(cord_val.y))
		{
			arr_val.push_back(std::stoi(informs[i * 3 + 2].second));
		}
	}
	return arr_val;
}
vec_2 vi_stuff::get_inform(int _val) {
	for (int i = 0; i < vi_arr.size(); i++) {
		if (informs[i * 3 + 2].second == std::to_string(_val)) 
		{
			
			return vec_2(std::stoi(informs[i * 3].second), std::stoi(informs[i * 3 + 1].second));
		}
	}
	return GR_::ground_99[0];
}

// GRAPHIC_ELEMENTS

// GRAPHIC_ELEMENT

// class graphic_element

graphic_element::graphic_element(vec_2 cord_value) {
	gr_cord = cord_value;
}
int graphic_element::gr_ff_out(std::string s_val)
{
	style_for_this(s_val);
	return 0;
}

//int graphic_element::gr_draw() {return 0;}

int graphic_element::set_cord(vec_2 cord_val) {
	gr_cord = cord_val;
	return 0;
}

vec_2 graphic_element::get_cord() {
	
	return gr_cord;
}

// class GR_STAT

int gr_stat::gr_s_w() {
	return gr_width;
}
int gr_stat::gr_s_h() {
	return gr_height;
}
int gr_stat::gr_clean() 
{
	for (int i = gr_cord.y; i < gr_s_h() + gr_cord.y; i++)
	{
		move(i + 1, gr_cord.x + 1);
		for (int j = gr_cord.x; j < gr_s_w() + gr_cord.x;
			j++)
		{
			style_for_this(" ");
		}
		std::cout << std::endl;
	}
	return 0;
}
char gr_stat::gr_get(vec_2 coord_value) {
	return gr_get_(coord_value.y, coord_value.x);
}

char gr_stat::gr_get_(int y, int x) {
	if (x >= gr_cord.x + gr_s_w()
		|| y >= gr_cord.y + gr_s_h()
			|| x < gr_cord.x
				|| y < gr_cord.y) return ' ';
	return gr_arr[y - gr_cord.y][x - gr_cord.x];
}

int gr_stat::gr_set(vec_2 cord_value, char c_val) {
	return gr_set(cord_value.y, cord_value.x, c_val);
}
int gr_stat::gr_set(int y, int x, char c_val) {
	if (x >= gr_cord.x + gr_width
		|| y >= gr_cord.y + gr_height
			|| x < gr_cord.x
				|| y < gr_cord.y) return -1;

	gr_arr[y - gr_cord.y][x - gr_cord.x] = c_val;
	return 0;
}

int gr_stat::gr_member() {
	clean_c_2arr(gr_arr, gr_height);
	gr_arr = get_c_2arr(gr_width, gr_height);
	//ground_fill();
	return 0;
}

int gr_stat::gr_remember(int w_val, int h_val) {
	if (gr_arr == NULL) {
		gr_width = w_val;
		gr_height = h_val;
		gr_member();
	}

	char** arr = get_c_2arr(w_val, h_val);
	// i on vertical | j on gorizont
	for (int i = 0; i < h_val; i++) 
	{
		for (int j = 0; j < w_val; j++) 
		{
			if ((i < gr_height) && (j < gr_width)) 
			{
				arr[i][j] = gr_arr[i][j];
			}
			else 
			{
				arr[i][j] = ' ';
			}
		}
	}
	clean_c_2arr(gr_arr, gr_height);
	gr_arr = arr;
	return 0;
}


// class GR_STAT_FILE gr_file, graphic_element with up file read

gr_stat_file::gr_stat_file(vec_2 cord_value, std::string file_name): gr_stat(cord_value) {

	if (_is_empty_file(file_name)) return;
	

	//gr_cord = cord_val;
	
		gr_file_ = file_read(file_name);

		gr_width = gr_file_.file_read_().find('\n'); // here will error, after to cape value = 0
		gr_height = gr_file_.file_read_().length() / (gr_width);
		// i dont know why +1 just it works

		gr_member();
		gr_f_fill();

		//gr_file_._clean();

	//grounrd_old();
	//fill_with_file();
}

int gr_stat_file::gr_f_fill() 
{
	std::string ground_of_file = gr_file_.file_read_();

	int i = 0, j = 0, ij = 0;

	while (i < ground_of_file.length()) 
	{
		if (ground_of_file[i] == '\n') 
		{
			j++;
			ij = -1;
		}
		else 
		{
			if (j < gr_height && ij < gr_width)
				gr_arr[j][ij] = ground_of_file[i];
		}
		i++; ij++;
	}
	return 0;
}

std::string gr_stat_file::get_name_file() 
{
	return gr_file_.get_name_file();
}

// class GR_DIN

int gr_din::gr_d_add(std::string item) 
{
	gr_d_arr.push_back(item);
	return 0;
}

int gr_din::gr_d_remove(int index) 
{
	if (index < 0 || index >= gr_d_arr.size()) return -1;
	gr_d_arr.erase(gr_d_arr.begin() + index);
	return 0;
}

std::string gr_din::gr_d_get(int ind) 
{
	if (ind < 0 || ind >= get_size()) return " ";
	return gr_d_arr[ind];
}
int gr_din::get_size() {
	return static_cast<int>(gr_d_arr.size());
}
int gr_din::gr_d_clean() 
{
	move(gr_cord.y + 1, gr_cord.x + 1);
	for (int i = 0; i < gr_d_arr.size(); i++)
	{
		for (int j = 0; j < gr_d_arr[i].length(); j++) {
			if (gr_d_arr[i][j] == '\n') {
				CO('\n');
				move_on_col(gr_cord.x);
			}
			else CO(' ');
		}
	}
	move_on_start();
	return 0;
}
int gr_din::gr_d_fill() 
{
	return 0;
}
int gr_din::gr_d_set(std::string item, int index) 
{
	if (index < 0 || index >= gr_d_arr.size()) 
	{ 
		std::cerr << "GR_DIN: ERROR IMPOSIBLE INDEX OF VECTOR\n";
		return -1; 
	}
	gr_d_arr[index] = item;
	return 0;
}
//gr_din::~gr_din() {}

// class selected_list

std::string selected_list::gr_d_get()
{
	if (selected_index < 0 || selected_index >= get_size()) return " ";
	return gr_d_arr[selected_index];
}

selected_list::selected_list(vec_2 cord_val, std::vector<std::string> items, int index, 
	GR_::color_joint items_value , GR_::color_joint selected_value)  : gr_din(cord_val)
{
	// clean vector gr_d_arr!!!!
	gr_d_arr = items;
	selected_index = index;
	joint_items = items_value;
	joint_selected = selected_value;
}

int selected_list::select_item(int index) 
{ // set
	if (index < 0 || index >= gr_d_arr.size()) return -1;
	selected_index = index;
	return 0;
}
int selected_list::selected_item_set(int index) 
{ // sum
	if (index + selected_index < 0 || index + selected_index >= gr_d_arr.size()) return -1;
	selected_index += index;
	return 0;
}
int selected_list::get_selected_index() 
{
	return selected_index;
}
int selected_list::gr_ff_out(std::string s_val) 
{
	
	if (s_val == gr_d_arr[selected_index]) 
	{
		style_for_this(joint_selected.joint_char_get() + s_val);
	}
	else 
	{
		style_for_this(joint_items.joint_char_get() + s_val);
	}
	move_on_col(gr_cord.x);
	return 0;
}

int selected_list::get_select_gr() {
	int move_result = 0;
	do
	{
		selected_item_set(move_result);
		//std::cerr << "Error of menu, selected_list of index selected, try to set imposible value\n";
		//menu_head();
		GR_::gr_draw(*this);
		move_result = move_for_menu();

		move_on_start();

	} while (move_result != -2);
	return get_selected_index();//1 событие ENTER
}

// GROUND
// F_GR_STAT_FILE  | with format symbols
//                <- GR_STAT_FILE
//                 -> GROUND | ground, map, many functions
// 


// class f_gr_stat_file

f_gr_stat_file::f_gr_stat_file(vec_2 cord_value, std::string file_name) : gr_stat_file(cord_value, file_name) {}

int f_gr_stat_file::type_symbol(char symbol)
{
	switch (symbol)
	{
	case '#':
		return 1;
	case ']':
		return 2;
	case '[':
		return 2;
	case '}':
		return 3;
	case '{':
		return 3;
	case '*':
		return 4;
	case '=':
		return 5;
	case '^':
		return 6;
	case 'N':
		return 7;
	default:
		return 0;
	}
}

int f_gr_stat_file::gr_ff_out(std::string s_val)
{
	std::string f_form = "";
	switch (type_symbol(s_val[0]))
	{
	case 1:
		f_form = GR_::color_of_wall.joint_char_get();
		break;
	case 2:
		f_form = GR_::color_of_door.joint_char_get();
		break;
	case 3:
		f_form = GR_::color_of_lift.joint_char_get();
		break;
	case 4:
		f_form = GR_::color_of_stuff.joint_char_get();
		break;
	case 5:
		f_form = GR_::color_of_trans.joint_char_get();
		break;
	case 6:
		f_form = GR_::color_of_subject.joint_char_get();
	default:
		break;
	}

	style_for_this(f_form + s_val);
	return 0;
}

// class ground

ground::ground(vec_2 coord_value, std::string file_name) :
	f_gr_stat_file(coord_value, NAME_FOLDER_GROUND + file_name)
{
	int max_count = check_max_count();
}

int ground::check_max_count()
{
	
	lie_count_max.x = (gr_width - gr_cord.x) / MAX_SIZE_WIDTH;
	lie_count_max.y = (gr_height - gr_cord.y) / MAX_SIZE_HEIGHT;
	//return (gr_width * gr_height) / (GR_::max_size_width * GR_::max_size_height);
	return 0;
}

vec_2 ground::get_lie_count() {
	return this->lie_count;
}

vec_2 ground::get_s_count(vec_2 cord_val)
{
	//if(cord_val.x < GR_::max_size_width )
	cord_val.x = (cord_val.x - gr_cord.x) / MAX_SIZE_WIDTH;
	cord_val.y = (cord_val.y - gr_cord.y) / MAX_SIZE_HEIGHT;
	return cord_val;
}

int ground::set_count(vec_2 cord_val)
{
	//if(cord_val.x < GR_::max_size_width )
	lie_count = get_s_count(cord_val);
	return 0;
}

int ground::gr_s_w()
{
	return  MAX_SIZE_WIDTH;
}
int ground::gr_s_h()
{
	return  MAX_SIZE_HEIGHT;
}

char ground::gr_get_(int y, int x)
{
	if(x < gr_cord.x
		|| y < gr_cord.y) return '=';
	if (((x + gr_s_w() * lie_count.x) >= gr_cord.x + std::min((gr_s_w() * (lie_count.x + 1)), gr_width))) 
	{
		if ((gr_s_w() * (lie_count.x + 1)) > gr_width) 
			return ' ';
		return '=';
	}
	if ((y + gr_s_h() * lie_count.y) >= gr_cord.y + std::min((gr_s_h() * (lie_count.y + 1)), gr_height)) 
	{
		if ((gr_s_h() * (lie_count.y + 1)) > gr_height)
			return ' ';
		return '=';
	}
	/*if (((x + gr_s_w() * lie_count.x) >= gr_cord.x + std::min((gr_s_w() * (lie_count.x + 1)), gr_width))
		|| ((y + gr_s_h() * lie_count.y) >= gr_cord.y + std::min((gr_s_h() * (lie_count.y + 1)), gr_height))
		|| x < gr_cord.x
		|| y < gr_cord.y)
	{
		if (x < gr_cord.x || y < gr_cord.y)
			return '=';

		if (((gr_s_w() * (lie_count.x + 1)) > gr_width) ||
			((gr_s_h() * (lie_count.y + 1)) > gr_height))
		{
			return ' ';
		}
		return '=';
	}*/

	return gr_arr[y + gr_s_h() * (lie_count.y) - gr_cord.y]
		[x + gr_s_w() * (lie_count.x) - gr_cord.x];
}

int ground::turn_virt()
{
	gr_virt_inf = vi_stuff(get_name_file());

	for (int i = 0; i < gr_height; i++) 
	{
		for (int j = 0; j < gr_width; j++) 
		{
			if (gr_arr[i][j] == '*') 
			{
				if (gr_virt_inf.get_inform(vec_2(j, i), 0) == -1) //|| gr_virt_inf.get_inform(vec_2(j, i)) == 27)
				{
					gr_arr[i][j] = '_';
				}
			}
		}
	}
	return 0;
}

int ground::get_stuff(vec_2 cord_val)
{
	cord_val = cord_val + (lie_count * GR_::gr_max_size);
	int stuff_val = gr_virt_inf.get_inform(cord_val - gr_cord, 1);
	if (stuff_val != -1)
		gr_set(cord_val, '_');
	return stuff_val;
}
std::vector<int> ground::get_stuffs()
{
	return gr_virt_inf.get_inform();
}
vec_2 ground::get_stuff(int _val) 
{
	vec_2 vec_2_val = gr_virt_inf.get_inform(_val);
	if (vec_2_val != GR_::ground_99[0]) return vec_2_val;
	return gr_cord;
}
vec_2 ground::get_stuff()
{
	return get_stuff(27);
}
int ground::set_stuff(person& _val, int _lvl_val, std::vector<int> arr_val) 
{
	//find 27 and to remake to cord_val

	gr_virt_inf.vi_write_tmp(_val.get_cord() + lie_count * GR_::gr_max_size, _val.health_prs.vl_get(), _lvl_val, arr_val);
	
	return 0;
}

int ground::is_stop(vec_2 cord_val)
{
	return type_symbol(gr_get(cord_val));
}
int ground::is_stop_for_(vec_2 cord_val)
{
	return type_symbol({ gr_arr[cord_val.y - gr_cord.y][cord_val.x - gr_cord.x] });
}
vec_2 ground::ground_door_move(vec_2 value)
{
	if (is_stop(value) != 2) return value;

	value.x += lie_count.x * gr_s_w();
	value.y += lie_count.y * gr_s_h();

	for (int i = value.x + 1;
		i < gr_width + gr_cord.x;
		i++) {
		if ((is_stop_for_({ i, value.y }) == 2))
		{
			return { i, value.y };
		}
	}
	for (int i = value.x - 1;
		i >= gr_cord.x;
		i--) {
		if ((is_stop_for_({ i, value.y }) == 2))
		{
			return { i, value.y };
		}
	}
	return value;
}

vec_2 ground::ground_lift_move(vec_2 value)
{
	if (is_stop(value) != 3) return value;

	value.x += lie_count.x * gr_s_w();
	value.y += lie_count.y * gr_s_h();

	for (int j = value.y + 1;
		j < gr_height + gr_cord.y;
		j++)
	{
		if ((is_stop_for_({ value.x, j }) == 3))
		{
			return { value.x , j };
		}
	}
	for (int j = value.y - 1;
		j >= gr_cord.y;
			j--)
	{
		if ((is_stop_for_({ value.x, j }) == 3))
		{
			return { value.x,j };
		}
	}
	return value;
}

int ground::ground_draw()
{
	// implementation for ground drawing

	GR_::gr_draw(*this);
	for (int i = gr_cord.y; i < gr_s_h() + gr_cord.y; i++) {
		move(i + 1, gr_cord.x); CO(" ");
	}
	move(gr_cord.y, gr_cord.x);
	for (int i = 0; i <= gr_s_w() + 1; i++) {
		CO(" ");
	}
	move(gr_cord.y + gr_s_h() + 1, gr_cord.x);
	for (int i = 0; i <= gr_s_w() + 1; i++) {
		CO(" ");
	}
	for (int i = gr_cord.y; i < gr_s_h() + gr_cord.y; i++) {
		move(i + 1, gr_cord.x + gr_s_w() + 1); CO(" ");
	}

	if (lie_count.x > 0)
	{
		for (int i = gr_cord.y; i < gr_s_h() + gr_cord.y; i++)
		{
			move(i + 1, gr_cord.x);
			gr_ff_out("=");
		}
	}
	if (lie_count.x < lie_count_max.x)
	{
		for (int i = gr_cord.y; i < gr_s_h() + gr_cord.y; i++)
		{
			move(i + 1, gr_cord.x + gr_s_w() + 1);
			gr_ff_out("=");
		}
	}
	if (lie_count.y > 0)
	{
		move(gr_cord.y, gr_cord.x);
		for (int i = 0; i <= gr_s_w() + 1; i++)
		{
			gr_ff_out("=");
		}
	}
	if (lie_count.y < lie_count_max.y)
	{
		move(gr_cord.y + gr_s_h() + 1, gr_cord.x);
		for (int i = 0; i <= gr_s_w() + 1; i++)
		{
			gr_ff_out("=");
		}
	}
	move_on_start(); // safery of on_col and on_row

	return 0;
}

int ground::ground_this_draw(vec_2 _val_arr) {

	std::string s_ = "";

	
		for (int ii = 0; ii < 3; ii++)
		{
			move(((_val_arr + GR_::ground_99[ii * 3]) + vec_2(1, 1)));
			for (int ij = 0; ij < 3; ij++)
			{
				s_ = "";
				s_.push_back(gr_get((_val_arr + GR_::ground_99[ii * 3 + ij]))); // i dont know why -1,-1 +
				gr_ff_out(s_);

				//std::cerr << s_;
			}
		}

	
	move_on_start();
	return 0;
}

//FUNCTION RETURNS NEW COORDINATE OR OLD COORDINATE OR (0,0)
vec_2 ground::get_stuck(vec_2 cord_val) {
	if ((is_stop(cord_val)) != 0) {
		for (int i = 0; i < 9; i++) {
			if (is_stop(cord_val + GR_::ground_99[i]) == 0) {
				return cord_val + GR_::ground_99[i];
			}
		}
		return vec_2(0,0);
	}
	return cord_val;
}

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



// CLASS VALUE
value::value(int val) {
	vl_val = val;
}
int value::vl_get() {
	return vl_val;
}
//CLASS HEALTH
health::health(int val) : value(val) {
	//health_value = val;
	if (vl_val <= 0)
	{
		health_status = GR_::DEAD;
	}
	else
	{
		health_status = GR_::ALIVE;
	}
}
int health::health_set(int val) {
	if ((val + vl_val) > 10) {
		vl_val = 10;
		health_status = GR_::ALIVE;
		return 1;
	}
	else if (val + vl_val < 0) {
		vl_val = 0;
		health_status = GR_::DEAD;
		return 0;
	}
	else {
		vl_val += val;
		health_status = GR_::ALIVE;
		return 1;
	}
	
}

//CLASS PROTECT

protect::protect(int val) : value(val) {
	//protect_value = value;
	protect_status = check_protect_class(val);
}
GR_::protect_class protect::check_protect_class(int val) {
	if (val < 3) {
		return GR_::LOW;
	}
	else if (val < 7) {
		return GR_::MEDIUM;
	}
	else {
		return GR_::HIGH;
	}
}
int protect::protect_set(int val) 
{
	if ((val + vl_val) > 7) 
	{
		vl_val = 7;
		//protect_status = GR_::;
	}
	else if (val + vl_val < 0) 
	{
		vl_val = 0;
	}
	else 
	{
		vl_val += val;
		protect_status = check_protect_class(vl_val);
	}
	return 0;
}
//int protect_get() { return protect_value; }
//void protect_set_minus(int value) {
	// Intentionally left empty for now
//}

// CLASS PRS_STAT
prs_stat::prs_stat(vec_2 cord_val, int health_value, char c_val) : gr_stat(cord_val),
	health_prs(health_value) {
	gr_width = 1; gr_height = 1;
	prs_fill(c_val);
}
int prs_stat::prs_fill(char c_val) {
	gr_member();
	gr_arr[0][0] = c_val;
	return 0;
}

//CLASS PERSON
person::person(vec_2 cord_val, int health_val, char c_val, int protect_val) : 
	prs_stat(cord_val, health_val, c_val), protect_person(protect_val) {}

// CLASS CONVOIR
//convoir::convoir(vec_2 cord_val) { convoir(cord_val, 5, 'C'); }
convoir::convoir(vec_2 cord_val, int health_val, char c_val) : prs_stat(cord_val, health_val, c_val){}
int convoir::cr_set_track(std::vector<vec_2> arr_val) 
{
	this->track = arr_val;
	track.push_back({ 0,0 });
	return 0;
}
vec_2 convoir::step_on_track() 
{
	//ДОЛЖНО РАБОТАТЬ ЭТО УСЛОВИЕ, НО НЕ РАБОТАЕТ...
	//if (track[track.size() - 1] == GR_::ground_99[4]) 
	//{
	// step.x - это индекс, step.y - это направление (-1, 1)
	//
	// 2
		step.x+=step.y;

		if (step.x == track.size() - 1 || step.x == -1) 
		{
			step.y *= -1;
			step.x += step.y;
		}

		track[track.size() - 1] = track[step.x];
	//}

	// 1
	if (track[track.size() - 1].x >= track[track.size() - 1].y) 
	{
		track[track.size() - 1] = track[track.size() - 1] + (GR_::ground_99[5]*step.y);
		return gr_cord + (GR_::ground_99[5] * step.y);
	}
	else 
	{
		track[track.size() - 1] = track[track.size() - 1] + (GR_::ground_99[7]*step.y);
		return gr_cord + (GR_::ground_99[7] * step.y);
	}
	//return 0;
}

vec_2 convoir::restep_on_track()
{
	// 1
	vec_2 cord_val;
	if (track[track.size() - 1].x >= track[track.size() - 1].y)
	{
		track[track.size() - 1] = track[track.size() - 1] - (GR_::ground_99[5] * step.y);
		cord_val = (GR_::ground_99[5] * step.y);
	}
	else
	{
		track[track.size() - 1] = track[track.size() - 1] - (GR_::ground_99[7] * step.y);
		cord_val = (GR_::ground_99[7] * step.y);
	}

	cord_val += gr_cord;

	// 2
	step.x -= step.y;

	if (step.x == track.size() - 1 || step.x == -1)
	{
		step.y *= -1;
		step.x -= step.y;
	}

	track[track.size() - 1] = track[step.x];

	return cord_val;
}

// CLASS VI_CONVOIRS
vi_convoirs::vi_convoirs(std::string s_val, char c_val) : virtual_information()
{
	set_name_file(GR_::get_v_name(GR_::get_be_name(s_val, POSTFIX_CONVOIR)));
	vi_fill();
	for (int i = 0; i < informs.size(); i+=3) 
	{
		vi_con_arr.push_back(convoir(vec_2(std::stoi(
			informs[i].second), std::stoi(informs[i + 1].second) )));
		vi_con_arr[vi_con_arr.size() - 1].cr_set_track( str_to_varr(informs[i + 2].second));
	}
}
int vi_convoirs::vi_draw_and_check(ground& gr_, vec_2 cord_val) 
{
	int j = -1;

	std::vector<vec_2> _vec_con_arr(vi_con_arr.size(), GR_::ground_99[0]);

	for (int i = 0; i < vi_con_arr.size(); i++) 
	{
		if (gr_.is_stop(vi_con_arr[i].get_cord()) != 1) 
		{
			if (GR_::_check_it_on_gr(vi_con_arr[i].get_cord(), gr_.get_cord() + (gr_.get_lie_count() * GR_::gr_max_size),
				gr_.get_cord() + ((gr_.get_lie_count() + GR_::ground_99[8]) * GR_::gr_max_size))) 
			{
				_vec_con_arr[i] = vi_con_arr[i].step_on_track();

				GR_::gr_this_draw(gr_, vi_con_arr[i].get_cord() - (gr_.get_lie_count() * GR_::gr_max_size));
				
			}
		}
	}

	for (int i = 0; i < _vec_con_arr.size(); i++)
	{
		if (_vec_con_arr[i] != GR_::ground_99[0] && std::find(_vec_con_arr.begin() + i + 1, _vec_con_arr.end(), _vec_con_arr[i])
			== _vec_con_arr.end()) 
		{

			if (_vec_con_arr[i] == cord_val)
			{
				j = i;
				vi_con_arr[i].restep_on_track();
			}

			else if(gr_.is_stop_for_(_vec_con_arr[i]) == 0) vi_con_arr[i].set_cord(_vec_con_arr[i]);

			vi_con_arr[i].set_cord(vi_con_arr[i].get_cord() - (gr_.get_lie_count() * GR_::gr_max_size));
			GR_::gr_draw(vi_con_arr[i]);
			vi_con_arr[i].set_cord(vi_con_arr[i].get_cord() + (gr_.get_lie_count() * GR_::gr_max_size));
		}
	}

	return j;
}


// LOKING ABOUT TO CROSSING
int vi_convoirs::vi_checky(vec_2 cord_val) 
{
	for (int i = 0; i < vi_con_arr.size(); i++) 
	{
		if (vi_con_arr[i].get_cord() == cord_val) 
		{
			return 1;
		}
	}
	return 0;
}
int vi_convoirs::_remote(int ind) {
	if (ind < 0 || ind >= this->vi_con_arr.size()) return 1;
	vi_con_arr[ind].gr_clean();
	vi_con_arr.erase(vi_con_arr.begin() + ind);
	return 0;
}

// CLASS STUFF
int stuff::gr_ff_out(std::string s_val)
{
	style_for_this(st_f.font_char_get() + st_cl.joint_char_get() + s_val);
	return 0;
}
int stuff::set_color(GR_::color_joint joint_val) 
{
	st_cl = joint_val;
	return 0;
}
GR_::type_stuff stuff::get_stuff() 
{
	return this->t_st;
}
// class INVENTORY

int inventory::set_index_selected(int index_val) 
{
	if (index_selected != -1) 
		items[index_selected].set_color(GR_::color_for_items);
	index_selected = index_val;
	items[index_selected].set_color(GR_::color_for_selected);
	return 0;
}
int inventory::get_index_selected() 
{
	return index_selected;
}
int inventory::get_size() 
{
	return static_cast<int>(items.size());
}
int inventory::_clean() 
{
	for (int i = 0; i < items.size(); i++) 
	{
		items[i].gr_clean();
	}
	return 0;
}
int inventory::inv_clean() 
{
	this->items.clear();
	return 0;
}
int inventory::gr_draw() 
{
	//_clean();
	for (int i = 0; i < items.size(); i++) 
	{
		if (i == index_selected) items[i].set_color(GR_::color_for_selected);
		GR_::gr_draw(items[i]);
	}
	return 0;
}

inventory::inventory(vec_2 cord_val) : graphic_element(cord_val) 
{
	//set_index_selected(1);
}

int inventory::add_item(int _val)
{

	if (_val < 0 || _val >= TYPE_STUFF_SIZE) return -1;
	items.push_back(stuff({ (gr_cord.x + static_cast<int>(items.size())
		* WIDTH_STUFF), gr_cord.y }, static_cast<GR_::type_stuff>(_val)));

	set_index_selected(static_cast<int>(items.size()) - 1);

	return 0;
}
int inventory::add_items(std::vector<int> arr_val)
{
	for (int i = 0; i < arr_val.size(); i++)
		add_item(arr_val[i]);
	return 0;
}

GR_::type_stuff inventory::get_item_stuff(int index)
{
	if (index < 0 || index >= items.size()) return GR_::type_stuff::DIARY;
	return items[index].get_stuff();
}
std::vector<int> inventory::get_items() {
	std::vector<int> arr;
	for (int i = 0; i < items.size(); i++)
	{
		arr.push_back(static_cast<int>(items[i].get_stuff()));
	}
	return arr;
}
int inventory::remove_item(int ind) 
{
	if (ind < 0 || ind >= items.size()) return -1;
	if (ind <= index_selected)
	{
		index_selected -= 1;
		if (index_selected == -1)
			index_selected = items.size() - 2; // с учётом удалённого элемента
	}

	for (int i = ind + 1; i < items.size(); i++) 
	{
		items[i].set_cord(items[i].get_cord() + (GR_::ground_99[3] * WIDTH_STUFF));
	}

	items.erase(items.begin() + ind);
	return 0;
}
int inventory::remove_items()
{
	items.erase(items.begin(), items.end());
	return 0;
}

GR_::type_stuff inventory::get_s_stuff() {
	return get_item_stuff(index_selected);
}
int inventory::remove_s() {
	return remove_item(index_selected);
}

// CLASS MENU
int menu::menu_head() {
	move(gr_cord.y, gr_cord.x + outstep);
	std::cout << GR_::font(GR_::font_names::UNDERLINE).font_char_get() << 
		GR_::color(GR_::color_names::RED, GR_::text_or_ground::TEXT).color_char_get()
			<< menu_title << GR_::font(GR_::font_names::RESET).font_char_get();
	return 0;
}
menu::menu(vec_2 cord_val, std::vector<std::string> arr_val,
	int ind, std::string title_val, GR_::color_joint cl_val_item, GR_::color_joint cl_val_selec) : 
		selected_list(cord_val, arr_val, ind, cl_val_item, cl_val_selec) 
{
	menu_title = title_val;
}

int menu::menu_draw() 
{

	// may be to remove it on SELECTED_LIST?
	//move_on_start();
	menu_head();
	return get_select_gr();
}
int menu::menu_clean() {
	move(gr_cord.y, gr_cord.x + outstep);
	for (int i = 0; i < menu_title.length(); i++) 
	{
		CO(' ');
	}

	this->gr_d_clean();
	return 0;
}
// GR_INF_HP CLASS
gr_user_inform::gr_user_inform(vec_2 cord_val) : 
	gr_din(cord_val + (GR_::gr_max_size_2 + vec_2(0, 8))) { gr_d_fill(); }

int gr_user_inform::gr_d_fill() {
	gr_d_add(GR_::color_of_wall.joint_char_get() + " hp: ");
	gr_d_add(" ");
	gr_d_add(GR_::color_of_wall.joint_char_get() + " pt: ");
	gr_d_add(" ");
	gr_d_add(GR_::color_of_wall.joint_char_get() + " x: ");
	gr_d_add(" ");
	gr_d_add(GR_::color_of_wall.joint_char_get() + " y: ");
	gr_d_add(" ");
	gr_d_add(GR_::color_of_wall.joint_char_get() + " using: ");
	gr_d_add(" ");
	gr_d_add("             ");
	return 0;
}
int gr_user_inform::us_update_(std::string val, int index) {
	return gr_d_set(val, (index) * 2 + 1);
}
int gr_user_inform::us_update_prsn(person& prsn) {
	us_update_(std::to_string(prsn.health_prs.vl_get()), 0);
	us_update_(std::to_string(prsn.protect_person.vl_get()), 1);
	us_update_(std::to_string(prsn.get_cord().x), 2);
	us_update_(std::to_string(prsn.get_cord().y), 3);
	return 0;
}
int gr_user_inform::us_update_cord(vec_2 cord_val) {
	us_update_(std::to_string(cord_val.x), 2);
	us_update_(std::to_string(cord_val.y), 3);
	return 0;
}
int gr_user_inform::us_update_hp(int hp) 
{
	us_update_(std::to_string(hp), 0);
	return 0;
}

//CLASS DIALOG

dialog::dialog(vec_2 cord_val) : gr_din(cord_val + GR_::ground_99[8] * 2),
	dg_select(cord_val + (GR_::ground_99[7] + GR_::ground_99[8] * 2), { "YES\n", "NO\n" }),
		title_stuff(static_cast<std::string> (NAME_FOLDER_GEN) + "dialog_title_stuff.txt"),
			_stuff(static_cast<std::string> (NAME_FOLDER_GEN) + "dialog_stuff.txt")
{
	gr_d_fill();
}

int dialog::gr_d_fill() 
{
	gr_d_add("");
	return 0;
}

int dialog::dg_accept(int ind) 
{
	gr_d_clean();
	dg_accept_inform(ind);

	if (dg_select.get_select_gr() == 0)
	{
		gr_d_clean();
		dg_select.gr_d_clean();
		return 1;
	}
	dg_select.gr_d_clean();
	this->gr_d_clean();
	return 0;
}

int dialog::dg_accept_inform(int ind) 
{
	gr_d_arr[0] = GR_::color_of_wall.joint_char_get() + title_stuff.get_inform(std::to_string(ind));
	GR_::gr_draw(*this);
	return 0;
}

int dialog::dg_accept_stuff(GR_::type_stuff t_st) 
{
	gr_d_clean();
	gr_d_arr[0] = GR_::color_of_wall.joint_char_get() + "`" +
		get_n_stuff(t_st) + "`" + _stuff.get_inform(get_n_stuff(t_st));
	GR_::gr_draw(*this);
	return 0;
}

int dialog::dg_set_cord(vec_2 cord_val) 
{
	set_cord(cord_val + (GR_::ground_99[8] * 2));
	this->dg_select.set_cord(cord_val + (GR_::ground_99[7] + GR_::ground_99[8] * 2));
	return 0;
}

// CLASS TALK_WINDOW
talk_window::talk_window(std::string file_name)
{
	outstep = 1;
	set_cord(vec_2(MAX_SIZE_WIDTH + 4, 3));

	virtual_information _vi_(file_name);

	int n = 0;

	for (int j = 0; j < _vi_.get_size(); j++) 
	{
		n = std::stoi(_vi_.get_item_inform(j + 1).second);

		std::vector<std::string> arr_val(n * 3);

		for (int i = 0; i < n * 3; i++)
		{
			arr_val[i] = _vi_.get_item_inform(j + i + 2).second;
		}

		std::string s_val = _vi_.get_item_inform(j).second;
		vec_2 _val = str_to_varr(s_val)[0];

		tw_arr.push_back({ _val, arr_val });

		j += n * 3 + 1;
	}
}
int talk_window::tw_update(vec_2 cord_val) 
{
	int index = 0, deep = 0, h = 0;

	for (int i = 0; i < tw_arr.size(); i++) {
		if (cord_val == tw_arr[i].first)
		{
			menu_title = tw_arr[i].second[0] + "\n";

			gr_d_arr.erase(gr_d_arr.begin(), gr_d_arr.end());

			for (int j = 1; j < 3; j++) 
			{
				this->gr_d_arr.push_back((tw_arr[i].second[j] + "\n"));
			}

			index = i;

			deep = 1;

			break;
		}
	}

	if (!deep) return -1;

	while (deep * 3 < tw_arr[index].second.size())
	{

		h = menu_draw();
		menu_clean();

		menu_title = tw_arr[index].second[3*(deep + h)] + "\n";

		gr_d_arr.erase(gr_d_arr.begin(), gr_d_arr.end());

		for (int j = 1; j < 3; j++)
		{
			this->gr_d_arr.push_back((tw_arr[index].second[3 * (deep + h) + j] + "\n"));
		}

		deep = deep*2*(h+1) + 1;
	}

	h = menu_draw();
	menu_clean();
	
	return h;
	
}

// CLASS LEVEL
level::level(std::string file_name, int ord_val) : virtual_information(GR_::get_be_name(file_name, POSTFIX_LEVEL))
{
	order = ord_val - 1; // можно по другому, рудемент от той версии где order всегда начинался с -1
	increment();
}
int level::increment() 
{

	return _set(order + 1);

}
int level::_draw() 
{
	if (order == -1) return -1;
	GR_::gr_draw(file_);
	while (!is_esc());
	//file_.gr_clean();
}
int level::_set(int ind)
{
	order = ind;

	if ((static_cast<int>(this->informs.size()) / 3) <= order) return -1;

	int k = -1;
	for (int i = 0; i < this->informs.size() / 3; i++)
	{
		if (std::stoi(this->get_item_inform(i * 3).second) == order)
		{
			k = i;
		}
	}

	if (k == -1)
		return -2;

	std::string v_ = get_item_inform(k * 3 + 1).second;
	cord_ = str_to_varr(v_)[0];

	file_ = f_gr_stat_file(GR_::ground_99[8], static_cast<std::string>(NAME_FOLDER_GROUND) + get_item_inform(k * 3 + 2).second); // надо что то делать с индексами одна ошибка и кают программе

	return 0;
}
vec_2 level::get_place_() 
{
	return cord_;
}
int level::get_order()
{
	return order;
}
// время когда люди хотели быть нейросетями, а нейросети хотели быть людьми