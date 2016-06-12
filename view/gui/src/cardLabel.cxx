#include <iostream>

#include <QEvent>

#include <gui/cardLabel.hxx>

static const int startX = 20; 
static const int startY = 290; 
static const int mWidth = 200;
static const int mHeight = 300;
static const int offSet = 10;

CardLabel::CardLabel(const Card* card, QWidget* pParent) :
QLabel(pParent),
_isSelected(false)
{
	fillCardLabel(card);
	connect(this, SIGNAL(cardLabelClickedSignal()), this, SLOT(cardLabelSelected()));
}
 
CardLabel::~CardLabel()
{

}

void CardLabel::fillCardLabel(const Card* card)
{
    setObjectName(QString::fromUtf8("cardLabel"));
    setText(QString(card->getName().c_str()));

    QPixmap pix(card->getFrame().c_str());
    setPixmap(pix.scaled(mWidth, mHeight, Qt::KeepAspectRatio));
}

void CardLabel::setPosition(const int pos)
{
	setGeometry(QRect(startX + pos * (mWidth+offSet), startY, mWidth, mHeight));
}

 bool CardLabel::event(QEvent *myEvent)
 {
 	switch(myEvent->type())
    {        
        case QEvent::MouseButtonRelease:
        {
 			emit cardLabelClickedSignal();
            break;        
        }
        default:
        	break;
    }
    return QWidget::event(myEvent);
 }

void CardLabel::cardLabelSelected()
{
	_isSelected = true;
}