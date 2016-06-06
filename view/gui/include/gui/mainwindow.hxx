#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>
#include <QtGui/QLabel>

#include <model/rules.hxx>
#include <model/playerContext.hxx>
#include <model/deck.hxx>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::vector<PlayerContext*> players, 
    					Deck* deck, 
    					Rules rules,
    					QWidget *parent = 0);
    ~MainWindow();

private slots:
    void drawCard();

private:
	void cleanLabels();
	void printPlayerHand(PlayerContext* player);

	//graphics
    Ui::MainWindow *ui;
    std::vector<QLabel*> _cardLabels;

    //models
    std::vector<PlayerContext*> _players;
	Deck* _deck;
	Rules _rules;
};

#endif // MAINWINDOW_HXX
