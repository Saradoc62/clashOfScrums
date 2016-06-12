#include <iostream>

#include <QEvent>

#include <gui/cardLabel.hxx>

static const int startX = 70; 
static const int startY = 50; 
static const int mWidth = 150;
static const int mHeight = 200;
static const int xOffSet = 10;
static const int yOffSet = 70;

CardLabel::CardLabel(const Card* card, QWidget* pParent) :
QLabel(pParent),
_card(card),
_xPos(0), 
_yPos(0),
_isSelected(false)
{
	fillCardLabel();
	setAttribute(Qt::WA_Hover);

	connect(this, SIGNAL(cardLabelClickedSignal()), this, SLOT(cardLabelSelected()));
}
 
CardLabel::~CardLabel()
{

}

void CardLabel::fillCardLabel()
{
    setObjectName(QString::fromUtf8("cardLabel"));
    setText(QString(_card->getName().c_str()));

    _pix = QPixmap(_card->getFrame().c_str());
    setPixmap(_pix.scaled(mWidth, mHeight, Qt::KeepAspectRatio));
}

void CardLabel::setPosition(const int xIndex, const int yIndex)
{
	_xPos = startX + xIndex * (mWidth + xOffSet);
	_yPos = startY + yIndex * (mHeight + yOffSet);

	setGeometry(QRect(_xPos, _yPos, mWidth, mHeight));
}

bool CardLabel::event(QEvent *myEvent)
{
	switch(myEvent->type())
{        
    case QEvent::MouseButtonRelease:
		emit cardLabelClickedSignal();
        break;        
    case QEvent::HoverEnter:
        hoverEnter();
        break;
	case QEvent::HoverLeave:
        hoverLeave();
        break;
	case QEvent::HoverMove:
        hoverMove();
        break;
    default:
    	break;
}
return QWidget::event(myEvent);
}

void CardLabel::cardLabelSelected()
{
	_isSelected = true;
}

void CardLabel::hoverEnter()
{
	static const int bigWidth = 200;
	static const int bigHeight = 250;

	setGeometry(QRect(_xPos, _yPos, bigWidth, bigHeight));
    setPixmap(_pix.scaled(bigWidth, bigHeight, Qt::KeepAspectRatio));

    this->raise();
}

void CardLabel::hoverLeave()
{
	setGeometry(QRect(_xPos, _yPos, mWidth, mHeight));
    setPixmap(_pix.scaled(mWidth, mHeight, Qt::KeepAspectRatio));
}

void CardLabel::hoverMove()
{
	
}
