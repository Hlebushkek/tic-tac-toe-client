#include "TicTacToeApp.hpp"
#include "LoginView.hpp"
#include "LinksView.hpp"
#include "StatisticView.hpp"

int main()
{
    TicTacToeApp *app = new TicTacToeApp();
    app->getMainWindow()->mainView = new LoginView();
    app->getMainWindow()->mainView->addSubview(new StatisticView());
    app->getMainWindow()->mainView->addSubview(new LinksView());
    app->Run();

    return 0;
}