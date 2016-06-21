#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>

#include <model/rules.hxx>
#include <model/playerContext.hxx>
#include <model/deck.hxx>

#include <gui/cardWidget.hxx>

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
    void drawHand();
    void endTurnAndSetNextPlayer();

private:
    void setBackGround();

	PlayerContext* getCurrentPlayer() const {return _currentPlayer;}
    void updatePlayerLabel(std::string const& name);

	void cleanHandWidgets();
    void cleanBoardWidgets();
    CardWidget* createWidget(const Card* card, const int xIndex, const LabelLocation location);
	void printPlayerHand(PlayerContext* player);
    void printPlayerBoard(PlayerContext* player);
    void printPlayerMoney(PlayerContext* player);
    void printPlayerContext(PlayerContext* player);

	//graphics
    Ui::MainWindow *ui;
    std::vector<CardWidget*> _handCardWidgets;
    std::vector<CardWidget*> _boardCardWidgets;

    //models
    int _internalTurnCount;
    std::string _imgPath;
    std::vector<PlayerContext*> _players;
    PlayerContext* _currentPlayer;
	Deck* _deck;
	Rules _rules;
};

#endif // MAINWINDOW_HXX
