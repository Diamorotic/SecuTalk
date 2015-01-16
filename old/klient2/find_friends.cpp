#include "find_friends.h"
#include "ui_find_friends.h"

find_friends::find_friends(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::find_friends)
{
    ui->setupUi(this);
}

find_friends::~find_friends()
{
    delete ui;

    connect(this->parent(), SIGNAL(set_user_data(user_data*)), this, SLOT(set_user_data(user_data*)));
    connect(this, SIGNAL(add_friend(int)),this->parent(), SLOT(add_friends(int)));
    connect(this, SIGNAL(find_user(user_data*)), this->parent(), SLOT(find_user(user_data*)));
}



//dostaliśmy z sieci dane szukanego użytkownika i chcemy je wyświetlić
void find_friends::set_user_data(user_data *)
{



}
