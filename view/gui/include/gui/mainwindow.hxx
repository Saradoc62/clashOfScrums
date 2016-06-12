#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>

#include <model/rules.hxx>
#include <model/playerContext.hxx>
#include <model/deck.hxx>

class CardLabel;

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
    void playCard();
    void endTurnAndSetNextPlayer();

private:
	PlayerContext* getCurrentPlayer() const {return _currentPlayer;}

	void cleanHandLabels();
    void cleanBoardLabels();
    CardLabel* createLabel(const Card* card, const int xIndex, const int yIndex);
	void printPlayerHand(PlayerContext* player);
    void printPlayerBoard(PlayerContext* player);
    void printPlayerMoney(PlayerContext* player);
    void printPlayerContext(PlayerContext* player);

	//graphics
    Ui::MainWindow *ui;
    std::vector<CardLabel*> _handCardLabels;
    std::vector<CardLabel*> _boardCardLabels;

    //models
    int _internalTurnCount;
    std::vector<PlayerContext*> _players;
    PlayerContext* _currentPlayer;
	Deck* _deck;
	Rules _rules;
};

#endif // MAINWINDOW_HXX
