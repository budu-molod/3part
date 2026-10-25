
#include "graphic_elements.h"

#ifdef _WIN32
#include <Windows.h>
#endif

int hist_draw(std::string s_val) {
    // вывод экрана с лором

    head_draw("HISTORY");
    text_draw(s_val,
        GR_::color(GR_::color_names::YELLOW, GR_::text_or_ground::TEXT));

    // ожидаем esc для выхода

    while (!is_esc());

    //очищение экрана перед новой итерациии menu

    clean_all();
    return 0;
}
int sety_draw(gr_stat_file& s_val, menu& _set_) {
    head_draw("SETINGS");
    //controls.set_cord({ 2,2 });
    GR_::gr_draw(s_val);
    int i = _set_.menu_draw();

    //while (!is_esc());
    s_val.gr_clean();
    _set_.gr_d_clean();
    //controls.set_cord({ MAX_SIZE_WIDTH + 4, 2 });
    //clean_all();
    clean_all();
    return i;
}
int inventory_drawing(inventory& _inv_for, dialog& _dialog, vec_2& i_dont_know, gr_user_inform& _ih, int* type_interface) 
{
    int _val;

    if (i_dont_know == vec_2(10, 5))
        i_dont_know = move_for_inv();

    if (i_dont_know == vec_2(-1, 0) ||
        i_dont_know == vec_2(1, 0))
    {
        if (!(((_inv_for.get_index_selected() + i_dont_know.x) >= _inv_for.get_size()) ||
            ((_inv_for.get_index_selected() + i_dont_know.x) < 0)))
        { 
            _inv_for.set_index_selected(
                _inv_for.get_index_selected() + i_dont_know.x);
            _dialog.dg_accept_stuff(_inv_for.get_s_stuff());
        }

    }
    else if (i_dont_know == vec_2(1, 3))
    {
        if (_dialog.dg_accept(1)) // IF USER WANTS TO USE THE STUFF
        {
            _val = get_i_stuff(_ih.gr_d_get(USER_ITEM));

            _ih.us_update_(get_n_stuff(_inv_for.get_s_stuff()), 4);
            _inv_for._clean();
            _inv_for.remove_s();

            if(_val != -1 && _val != 2 && _val != 4) 
                _inv_for.add_item(_val);

            _inv_for.gr_draw();
            GR_::gr_draw(_ih);
            *type_interface = 112;

            return get_i_stuff(_ih.gr_d_get(USER_ITEM));
        }
    }
    return -1;
}

int convoir_statement(gr_user_inform& _ih, dialog& _dialog, vi_convoirs& convoirs, int& menu_select, person& personer, int _is_2) {
    if (_ih.gr_d_get(USER_ITEM) == "blade" && _dialog.dg_accept(3))
    {
        _ih.gr_d_set("", USER_ITEM);
        convoirs._remote(_is_2);
    }
    else
    {
        if (!personer.health_prs.health_set(-2))
        {

            menu_select = -2;
            //break;
            return 1;
        }

        _ih.us_update_hp(personer.health_prs.vl_get());
        GR_::gr_draw(_ih);

        _dialog.dg_accept_inform(7);
    }
    return 0;
}

int all_draw(gr_stat& br_, ground& _ground, inventory& _inv_for, gr_din& _ih) {
    GR_::gr_draw(br_);
    _inv_for.gr_draw();
    _ground.ground_draw();
    //_ih.us_update_(std::to_string(personer.health_person.vl_get()), 0);

    GR_::gr_draw(_ih);
    return 0;
}
int all_clean(gr_stat& br_, ground& _ground, inventory& _inv_for, gr_din& _ih) {
    br_.gr_clean();
    _inv_for._clean();
    _ground.gr_clean();
    //_ih.us_update_(std::to_string(personer.health_person.vl_get()), 0);

    _ih.gr_d_clean();
    return 0;
}

//int check_y()
int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif // _WIN32
    //int***************************************** x;
    hidde_cursor();
    // may be to make new class GAME with every oblect?
    file_read hist(static_cast<std::string> (NAME_FOLDER_HISTORY) + "history_start.txt");
    
    dialog _dialog;

    f_gr_stat_file title({ 2,2 }, static_cast<std::string> (NAME_FOLDER_GEN) + "gen.txt");
    f_gr_stat_file game_over({ 2,2 }, static_cast<std::string> (NAME_FOLDER_GEN) + "game_over.txt");

   // f_gr_stat_file 
    clean_all();
    GR_::gr_draw(title);
    while (!is_esc());
    //очищение экрана перед новой итерациии menu
    clean_all();

    gr_stat_file br_({ 0,0 }, static_cast<std::string> (NAME_FOLDER_GEN) + "border.txt");
    gr_stat_file controls({ 2, 2 }, static_cast<std::string> (NAME_FOLDER_GEN) + "control.txt");

    menu _setting_({ 2, 13 }, GR_::get_file_names(NAME_FOLDER_GROUND, POSTFIX_VIRTUAL_INFORMATION, 1), 0, "GROUNDS");

    ground _ground({ 2,2 }, GR_::pop_(_setting_.gr_d_get()));
    _ground.turn_virt();
    person personer(_ground.get_stuff(), ~_ground.get_stuff(11), 'P', 3);
    _ground.set_count(personer.get_cord());
    personer.set_cord(personer.get_cord() - (_ground.get_lie_count() * GR_::gr_max_size));

    inventory _inv_for;
    _inv_for.add_items((_ground.get_stuffs()));

    vi_convoirs convoirs(static_cast<std::string> (NAME_FOLDER_GROUND)+ GR_::pop_(_setting_.gr_d_get()));
    // ожидать какое-то количество времени
    personer.set_cord(_ground.get_stuck(personer.get_cord()));

    int _is_ = 0, _is_2 = 12, set_val = 0;

    vec_2 i_dont_know, i_yet;
    
    int type_interface = 112;

    //int is_stop;
    menu _menu;
    int menu_select = 0;

    gr_user_inform _ih({ 4,0 });

    talk_window _talk(static_cast<std::string> (NAME_FOLDER_GROUND) + GR_::get_be_name(GR_::pop_(_setting_.gr_d_get()), POSTFIX_TALK));
    
    level _level(static_cast<std::string> (NAME_FOLDER_GROUND) + GR_::pop_(_setting_.gr_d_get()), ~_ground.get_stuff(151));
    //_level.increment();
    _ground.gr_set(_level.get_place_(), '^');

    

   do {
       if (menu_select == -2) game_over.gr_clean();
        menu_select = _menu.menu_draw();

        _menu.gr_d_clean();
        
        if (menu_select == 1) {

            hist_draw(hist.file_read_());

        }
        if (menu_select == 2) 
        {
            sety_draw(controls, _setting_);

            if (NAME_FOLDER_GROUND + _setting_.gr_d_get() != _ground.get_name_file())
            {
                // func _1
                _ground.set_stuff(personer, _level.get_order(), _inv_for.get_items());
                _ground = ground({ 2,2 }, GR_::pop_(_setting_.gr_d_get()));
                _ground.turn_virt();

                personer.set_cord(_ground.get_stuff());
                _ground.set_count(personer.get_cord());
                personer.set_cord(personer.get_cord() - (_ground.get_lie_count() * GR_::gr_max_size));

                convoirs = vi_convoirs(static_cast<std::string> (NAME_FOLDER_GROUND) + (GR_::pop_(_setting_.gr_d_get())));
                
                _level = level(static_cast<std::string> (NAME_FOLDER_GROUND) + GR_::pop_(_setting_.gr_d_get()), ~_ground.get_stuff(151));

                _ground.gr_set(_level.get_place_(), '^');

                _inv_for.inv_clean();

                _inv_for.remove_items();
                _inv_for.add_items((_ground.get_stuffs()));

                // end
                //_dialog.gr_d_clean();
            }
        }
        if (menu_select == 0) 
        {
            _ih.us_update_prsn(personer);
            _ih.us_update_cord(personer.get_cord() + _ground.get_lie_count() * GR_::gr_max_size);
            all_draw(br_, _ground, _inv_for, _ih);
            //_ih.us_update_(std::to_string(personer.health_person.vl_get()), 0
            //controls.gr_draw();
        }
        while (menu_select == 0) 
        {
            if(type_interface == 112) 
            {
				//pr_arr[0] = personer.get_cord();
                _ground.ground_this_draw((personer.get_cord()));
                GR_::gr_draw(personer);
                
                _ih.us_update_prsn(personer);
                _ih.us_update_cord(personer.get_cord() + _ground.get_lie_count()*GR_::gr_max_size);

                GR_::gr_draw(_ih);
            }
			else if (type_interface == 105) 
            {
                _inv_for.gr_draw();
			}

            // обработка события клавиши
            _is_ = 0; _is_2 = 0;
            while (( !_kbhit() || _is_ != -1)&& type_interface == 112)
            {
                _is_++;
                /*
                if (_is_2 == 12) 
                {
                    if (personer.gr_get(personer.get_cord()) == 'P') personer.gr_set(personer.get_cord(), 'R');
                    else if (personer.gr_get(personer.get_cord()) == 'R')personer.gr_set(personer.get_cord(), 'P');
                    GR_::gr_draw(personer);
                    _is_2 = -1;
                }*/
                if (type_interface == 112 && _is_ == 5) 
                {
                    // it`s bad, but while i keep it  so now
                    _is_2 = convoirs.vi_draw_and_check(_ground, personer.get_cord()); //DOING STEP ALL CONVOIRS, SO CHECKING OF STUCK PERSON AND CONVOIRS

                    if (_is_2 != -1) 
                    { // надо совместить с gr_draw(personer) рисовать без шага
                        if (convoir_statement(_ih, _dialog, convoirs, menu_select, personer, _is_2))
                            break;
                    } 
                    GR_::gr_draw(personer);
                    _is_ = -1;
                }
                if (menu_select == -2) break;
                //if (convoirs.vi_checky(i_yet + (_ground.get_lie_count() * GR_::gr_max_size)))
                    //_dialog.dg_accept(3);
                _is_2++;
                
                wait(30);
            }

            if (menu_select == -2)
                break;

            i_dont_know = move_for_game();
            //wait(70);

            if(type_interface == 112) 
                i_yet = personer.get_cord() + i_dont_know;

            if (i_dont_know == vec_2(2, 7)) 
            {
                clean_all();
                menu_select = -1;
                break;
            }
            else if (i_dont_know == vec_2(10, 5)) 
            {
                type_interface = 105;
            }
            else if (i_dont_know == vec_2(11, 2)) 
            {
                type_interface = 112;
            }
            else if (type_interface == 112 && i_dont_know == vec_2(1, 3))
                i_yet = personer.get_cord() + GR_::ground_99[4];

            // Обработка исключительных событий: стена, дверь, если всё в порядке - то перемещение
            
            //PERSONER ON GROUND INTERFACE
            if (type_interface == 112) 
            {
                if (i_dont_know == vec_2(11, 2)) 
                {
                    i_dont_know = move_for_hands();
                    i_yet = personer.get_cord() + i_dont_know;
                }
                // FUNCTION OF TO CHECKING CONVOIRS
                if (convoirs.vi_checky(i_yet + (_ground.get_lie_count() * GR_::gr_max_size))) 
                {
                    if (convoir_statement(_ih, _dialog, convoirs, menu_select, personer, _is_2))
                        break;

                    continue;

                    //else if (_ih.gr_d_get(USER_ITEM) == "hleb" && )
                }
                //is_stop = ;
                switch (_ground.is_stop(i_yet)) 
                {
                case 1: 

                    break;

                case 2:
                    GR_::gr_this_draw(_ground, personer.get_cord());
                    personer.set_cord(_ground.
                        ground_door_move(i_yet));

                    if (!(_ground.get_s_count(personer.get_cord())
                        == _ground.get_lie_count())) 
                    {
                        _ground.set_count(personer.get_cord());

                        _ground.ground_draw();
                    }

                    personer.set_cord( personer.get_cord() - 
                        (_ground.get_lie_count()*GR_::gr_max_size));

                    break;

                case 3:

                    GR_::gr_this_draw(_ground, personer.get_cord());
                    personer.set_cord(_ground.
                        ground_lift_move(i_yet));

                    if (!(_ground.get_s_count(personer.get_cord())
                        == _ground.get_lie_count()))
                    {
                        _ground.set_count(personer.get_cord());

                        _ground.ground_draw();
                    }

                    personer.set_cord({ personer.get_cord() - 
                        (_ground.get_lie_count() * GR_::gr_max_size) });

                    break;

                case 4: // STUFF

                    if (_inv_for.get_size() < MAX_SIZE_INVENTORY) // CHECK FOR MAX
                    {
                        if (_dialog.dg_accept(0)) // ANSWER ABOUT TAKING
                        {
                            _inv_for.add_item(_ground.get_stuff(i_yet)); // ADD STUFF ITEM ON INVENTORY
                            //personer.set_cord(i_yet); // ->
                            //_inv_for.gr_draw(); // DRAW INVENTORY
                            _dialog.dg_accept_stuff(_inv_for.get_s_stuff()); // DRAW STUFF INFORMATION ON DIALOG_PART
                        }
                    }
                    else if (_dialog.dg_accept(2))// ANSWER ABOUT REMOVED AND ADD
                    {
                        _inv_for._clean();
                        _inv_for.remove_s(); // DELETE SELECTED ITEM
                        _inv_for.add_item(_ground.get_stuff(i_yet));
                        //personer.set_cord(i_yet); // ->
                        //_inv_for.gr_draw(); // DRAW INVENTORY
                        _dialog.dg_accept_stuff(_inv_for.get_s_stuff()); // DRAW STUFF INFORMATION ON DIALOG_PART
                    }

                    _inv_for.gr_draw(); // DRAW INVENTORY

                    personer.set_cord(i_yet);

                    break;

                case 5:

                    _ground.set_count(i_yet + (_ground.get_lie_count() * GR_::gr_max_size));
                    _ground.ground_draw();

                    // UNDERSTOOD WHERE I WILL GO AFTER SWAP IN OTHER GROUND PART
                    if (i_yet.x >= _ground.gr_s_w()) // I WENT IN RIGHT, I`LL GO IN LEFT
                    {
                        personer.set_cord({
                            i_yet.x - _ground.gr_s_w(), i_yet.y });
                    }
                    else if (i_yet.x <= _ground.get_cord().x) // I WENT IN LEFT, I`LL GO IN RIGHT
                    {
                        personer.set_cord({
                            _ground.gr_s_w() + i_yet.x, i_yet.y });
                    }
                    else if (i_yet.y >= _ground.gr_s_h()) // I WENT IN DOWN, I`LL GO IN UP
                    {
                        personer.set_cord({ i_yet.x,
                            i_yet.y - _ground.gr_s_h() });
                    }
                    else if (i_yet.y <= _ground.get_cord().y) // I WENT IN UP, I`LL GO IN DOWN
                    {
                        personer.set_cord({ i_yet.x,
                            _ground.gr_s_h() + i_yet.y });
                    }

                    // CHECK FOR STUCK (WALL) IN GROUND
                    personer.set_cord(_ground.get_stuck(personer.get_cord()));

                    break;

                case 6:

                    all_clean(br_, _ground, _inv_for, _ih);

                    _level._draw();
                    _ground.gr_set(_level.get_place_(), '_');
                    _level.increment();

                    _ground.gr_set(_level.get_place_(), '^');

                    all_draw(br_, _ground, _inv_for, _ih);

                    break;
                case 7: // TALKINK WITH NPS

                    if (_ih.gr_d_get(USER_ITEM) == "dictionary")
                    {
                        if(_dialog.dg_accept(5))
                            _talk.tw_update(i_yet + _ground.get_lie_count() * GR_::gr_max_size);
                    }
                    else 
                    {
                        _dialog.dg_accept_inform(6);
                    }

                    break;
                default:
                    personer.set_cord(i_yet);
                }
                
            }

            //INVENTORY INTERFACE
            // mb to remote on func? there to count all _INVENTORY_?
            else if (type_interface == 105) 
            {
                _is_ = inventory_drawing(_inv_for, _dialog, i_dont_know, _ih, &type_interface); // I USED _is_ LIKE JUST VALUE
                
                if (_is_ == 2)
                    personer.health_prs.health_set(1);

                if (_is_ == 4)
                    personer.protect_person.protect_set(1);

            }
            move_on_start();
        }

        if (menu_select == -2)
        {

            GR_::delete_file(GR_::get_v_name(GR_::get_be_name(_ground.get_name_file(), POSTFIX_TMP)));

            all_clean(br_, _ground, _inv_for, _ih);

            //func _1
            _ground = ground({ 2,2 }, GR_::pop_(_setting_.gr_d_get()));
            _ground.turn_virt();

            personer.health_prs.health_set(~_ground.get_stuff(11) - personer.health_prs.vl_get());
            personer.set_cord(_ground.get_stuff());
            _ground.set_count(personer.get_cord());
            personer.set_cord(personer.get_cord() - (_ground.get_lie_count() * GR_::gr_max_size));

            convoirs = vi_convoirs(static_cast<std::string> (NAME_FOLDER_GROUND) + (GR_::pop_(_setting_.gr_d_get())));

            _level._set(0);
            _ground.gr_set(_level.get_place_(), '^');

            _inv_for.inv_clean();
            // end

            GR_::gr_draw(game_over);

            while (!is_esc());
        }
   } 
   while (menu_select != 3);

   clean_all();

   _dialog.dg_set_cord({ 0,0 });

   if (!_dialog.dg_accept(4)) // SAVE or save
   {
       GR_::delete_file_tmp(NAME_FOLDER_GROUND);
   }
   else
        _ground.set_stuff(personer, _level.get_order(), _inv_for.get_items());

   return 0;
}
