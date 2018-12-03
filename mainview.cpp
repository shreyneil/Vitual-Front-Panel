#include "mainview.h"
#include "ui_mainview.h"
#include "setuptab.h"
#include "controltab.h"
#include "aboutbox.h"

MainView::MainView(QWidget *parent, SetupTab& setup, ControlTab& controlTab) :
    QMainWindow(parent),
    m_setupTab(setup),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    m_setupTab.setParent(this);
    controlTab.setParent(this);//not creating a member variable here.
    ui->loSetupTab->addWidget(&m_setupTab);
    ui->loControlTab->addWidget(&controlTab);
    //Alternate use of setuptab using a contructer instead of a direct parameter to the mainview class.
    /*
    auto setup_tab = new SetupTab(this);
    ui->loSetupTab->addWidget(setup_tab);
    */

}

MainView::~MainView()
{
    delete ui;
}

void MainView::on_action_Exit_triggered()
{
    QApplication::quit();
    //help docs mentions to connect this static method quit to the last window close option.
}

void MainView::on_action_About_triggered()
{
    //TODO
    AboutBox about_box;
    about_box.show();
    about_box.exec();
    //if we end at the show method the method ends as it goes out of scope.
    //exec helps prevent that.
}
