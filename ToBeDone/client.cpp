

messenger 
{
        talker t;
        login_window l;

        login_window::slot () {
                if ( new user is set ) {
                        m_messenger->register_user(name);//talker->send_command();
                } else {
                        m_messenger->login_user(name);
                }
        }
        users_window m;

        l->show(); 
        m->hide();
}

int main(int argc, char** argv)
{
        QApp app(argc, argv);
        messenger m; // connect
        m.show_login_window(); 
        return app.run();
}
