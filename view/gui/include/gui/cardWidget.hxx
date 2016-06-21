#ifndef CARDWIDGET_HXX
#define CARDWIDGET_HXX

#include <QtGui/QLabel>

#include <model/card.hxx>

enum LabelLocation
{
	inBoard, 
	inHand
};

class CardWidget : public QLabel
{
Q_OBJECT

public:
    CardWidget(const Card* card, QWidget* pParent = 0);
    virtual ~CardWidget();

    //getters
    const bool isSelected() const {return _isSelected;}
    const bool isEnlarged() const {return _isEnlarged;}
    const LabelLocation location() const {return _location;}

    //setters
    void setSelected(const bool mode) {_isSelected = mode;}
    void setLocation(const LabelLocation loc) {_location = loc;}

    void setPosition(const int xIndex, const LabelLocation location);

signals:
	void cardWidgetClickedSignal();
	void hoverLeaveSignal();

protected:
	 bool event(QEvent *myEvent);

private:
	void refreshCardNameLabel();
	void refreshCardCostLabel();
    void fillCardWidget();
    void hoverEnter();
    void hoverLeave();
    void hoverMove();

    //models
    const Card* _card;
    std::string _backgroundPath;
    QLabel _name;
    QLabel _cost;
    QPixmap _bckgndPix;
    QPixmap _pix;
    int _xPos;
    int _yPos;

    //sate
    bool _isSelected;
    bool _isEnlarged;
    LabelLocation _location;
};

#endif //CARDWIDGET_HXX
