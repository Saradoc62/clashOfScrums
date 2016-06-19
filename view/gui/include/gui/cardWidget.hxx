#ifndef CARDWIDGET_HXX
#define CARDWIDGET_HXX

#include <QtGui/QLabel>

#include <model/card.hxx>

class CardWidget : public QWidget
{
Q_OBJECT

public:
    CardWidget(const Card* card, QWidget* pParent = 0);
    virtual ~CardWidget();

    //getters
    const bool isSelected() const {return _isSelected;}

    void setPosition(const int xIndex, const int yIndex);

signals:
	void cardWidgetClickedSignal();	

public slots:
    void cardWidgetSelected();

protected:
	 bool event(QEvent *myEvent);

private:
    void fillCardWidget();
    void hoverEnter();
    void hoverLeave();
    void hoverMove();

    const Card* _card;
    QLabel _frame;
    QLabel _name;
    QPixmap _pix;
    int _xPos;
    int _yPos;
    bool _isSelected;
};

#endif //CARDWIDGET_HXX
