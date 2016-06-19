#include <iostream>

#include <QEvent>

#include <gui/cardWidget.hxx>

//Card Widget
static const int startX = 70; 
static const int startY = 50; 
static const int mWidth = 150;
static const int mHeight = 200;
static const int xOffSet = 10;
static const int yOffSet = 70;

//Card frame
static const int fWidth = mWidth/2;
static const int fHeight = mHeight/2;
static const int fMarginX = (mWidth - fWidth)/2;
static const int fMarginY = 10;

//Card name
static const int nWidth = mWidth/2;
static const int nHeight = mHeight/2;
static const int nMarginX = (mWidth - fWidth)/2;
static const int nMarginY = 70;

CardWidget::CardWidget(const Card* card, QWidget* pParent) :
QWidget(pParent),
_card(card),
_name(this),
_frame(this),
_xPos(0), 
_yPos(0),
_isSelected(false)
{
	//fillCardWidget();
	setAttribute(Qt::WA_Hover);

	connect(this, SIGNAL(cardWidgetClickedSignal()), this, SLOT(cardWidgetSelected()));
}
 
CardWidget::~CardWidget()
{

}

void CardWidget::fillCardWidget()
{
	//Card name
    const int nPosX = this->x() + nMarginX;
    const int nPosY = this->y() + nMarginY;
    _name.setGeometry(QRect(nPosX, nPosY, nWidth, nHeight));
    _name.setText(QString(_card->getName().c_str()));

    //Card frame
    const int fPosX = this->x() + fMarginX;
    const int fPosY = this->y() + fMarginY;
    _frame.setGeometry(QRect(fPosX, fPosY, fWidth, fHeight));
    _pix = QPixmap(_card->getFrame().c_str());
    _frame.setPixmap(_pix.scaled(fWidth, fHeight, Qt::KeepAspectRatio));
}

void CardWidget::setPosition(const int xIndex, const int yIndex)
{
	_xPos = startX + xIndex * (mWidth + xOffSet);
	_yPos = startY + yIndex * (mHeight + yOffSet);

	setGeometry(QRect(_xPos, _yPos, mWidth, mHeight));
	setStyleSheet("border: 4px solid black; border-radius: 10px;");
}

bool CardWidget::event(QEvent *myEvent)
{
	switch(myEvent->type())
{        
    case QEvent::MouseButtonRelease:
		emit cardWidgetClickedSignal();
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

void CardWidget::cardWidgetSelected()
{
	_isSelected = true;
}

void CardWidget::hoverEnter()
{
	//Card Widget
	const int mBigWidth = 200;
	const int mBigHeight = 250;
	setGeometry(QRect(_xPos, _yPos, mBigWidth, mBigHeight));

	//Card Frame
	const int fBigWidth = mBigWidth/2;
	const int fBigHeight = mBigHeight/2;
	const int fPosX = this->x() + fMarginX;
    const int fPosY = this->y() + fMarginY;
    _frame.setPixmap(_pix.scaled(fBigWidth, fBigHeight, Qt::KeepAspectRatio));
    //_frame.setGeometry(QRect(fPosX, fPosY, fBigWidth, fBigHeight));

    //Card Name

   	raise();
}

void CardWidget::hoverLeave()
{
	setGeometry(QRect(_xPos, _yPos, mWidth, mHeight));

	//card frame
	//_frame.setGeometry(QRect(fPosX, fPosY, fWidth, fHeight));
    _frame.setPixmap(_pix.scaled(fWidth, fHeight, Qt::KeepAspectRatio));
}

void CardWidget::hoverMove()
{
	
}
