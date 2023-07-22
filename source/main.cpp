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
    app->getMainWindow()->mainView->addSubview(loginView);

    //Login Button
    GUIButton *loginButton = new GUIButton("Login In");
    loginButton->setButtonAction([loginView, app](GUIView *sender) {
        std::cout << "Login in with credentials: " << loginView->getLogin() << " " << loginView->getPassword() << std::endl;
        app->getClient().loginIn(loginView->getLogin(), loginView->getPassword());
    });
    loginView->addSubview(loginButton);

    //Statistic View
    loginView->addSubview(new StatisticView());

    //Links View
    LinksView *linksView = new LinksView();
    loginView->addSubview(linksView);

    //Github button
    GUIButton *githubButton = new GUIButton("We on GitHub", "../resources/github-mark-white.png");
    githubButton->setButtonAction([](GUIView *sender) {
        std::system("start https://github.com/Hlebushkek/tic-tac-toe-client");
    });
    linksView->addSubview(githubButton);

    //Run
    app->Run();

    return 0;
}