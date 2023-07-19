#include <iostream>
#include <cstdlib>
#include "TicTacToeClient.hpp"
#include "TicTacToeApp.hpp"
#include "LoginView.hpp"
#include "LinksView.hpp"
#include "StatisticView.hpp"
#include "GUIButton.hpp"

int main()
{
    TicTacToeApp *app = new TicTacToeApp();

    //Login View
    LoginView *loginView = new LoginView();
    app->getMainWindow()->mainView = loginView;

    //Login Button
    GUIButton *loginButton = new GUIButton();
    loginButton->title = "Login In";
    loginButton->setButtonAction([loginView, app](GUIView *sender) {
        std::cout << "Login in with credentials: " << loginView->getLogin() << " " << loginView->getPassword() << std::endl;
        app->getClient().loginIn(loginView->getLogin(), loginView->getPassword());
    });
    loginView->addSubview(loginButton);

    //Statistic View
    app->getMainWindow()->mainView->addSubview(new StatisticView());

    //Links View
    LinksView *linksView = new LinksView();
    app->getMainWindow()->mainView->addSubview(linksView);

    //Github button
    GUIButton *githubButton = new GUIButton();
    githubButton->title = "We on Github";
    githubButton->setButtonAction([](GUIView *sender) {
        std::system("start https://github.com/Hlebushkek/tic-tac-toe-client");
    });
    linksView->addSubview(githubButton);

    //
    app->Run();

    return 0;
}