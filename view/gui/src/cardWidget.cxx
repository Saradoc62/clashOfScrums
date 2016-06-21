#include <iostream>

#include <QEvent>

#include <gui/cardWidget.hxx>
#include <configuration.h>

static const float mScaleFactor = 1.25;

//Card Widget
static const int startX = 70; 
static const int startY = 80;

static const int mWidth = 150;
static const int mHeight = 200;
static const int mXHandOffSet = -70; //negative number will overlap cards
static const int mXBoardOffSet = 10; //margin between cards
static const int mYOffSet = 70;
static const int mRaiseOffset = -100; //raise card when hovering

CardWidget::CardWidget(const Card* card, QWidget* pParent) :
QLabel(pParent),
_card(card),
_name(this),
_cost(this),
_xPos(0), 
_yPos(0),
_isSelected(false),
_isEnlarged(false),
_location(inHand)
{
	setAttribute(Qt::WA_Hover);

	_backgroundPath = std::string(RESOURCES_PATH) + "PNGs/template.png";
	fillCardWidget();
}
 
CardWidget::~CardWidget()
{

}

void CardWidget::fillCardWidget()
{
	//Card Background
    _bckgndPix = QPixmap(_backgroundPath.c_str());
    setPixmap(_bckgndPix.scaled(mWidth, mHeight, Qt::KeepAspectRatio));
 
    //Card frame
    /*const int fPosX = this->x() + fMarginX;
    const int fPosY = this->y() + fMarginY;
    _frame.setGeometry(QRect(fPosX, fPosY, fWidth, fHeight));
    _pix = QPixmap(_card->getFrame().c_str());
    _frame.setPixmap(_pix.scaled(fWidth, fHeight, Qt::KeepAspectRatio));*/
}

void CardWidget::refreshCardCostLabel()
{
	//get scale factor
	const float factor = isEnlarged() ? mScaleFactor : 1.f;

	//Geometry
	const int nWidth = width() - 52; 
	const int nPosX = (width() - nWidth)/2;

	const int heightMagicNumber = 12; //12 depends on card background
	const float nHeight = heightMagicNumber * factor; 
	const float nPosY = nHeight;

	_cost.setGeometry(QRect(nPosX, int(nPosY), nWidth, int(nHeight)));

	//Text and font
	float fontSize = (heightMagicNumber - 1) * factor;
	QFont f("Arial", int(fontSize), QFont::Bold);
  	_cost.setFont(f);
	_cost.setAlignment(Qt::AlignRight); //Align right
	_cost.setText(QString::number(_card->getCost()));
}

void CardWidget::refreshCardNameLabel()
{
	//get scale factor
	const float factor = isEnlarged() ? mScaleFactor : 1.f;

	//Geometry
	const int nWidth = width() - 10; //10 to keep margins each sides
	const int nPosX = (width() - nWidth)/2; //center on x axis

	const int heightMagicNumber = 12; //12 depends on card background
	const float nHeight = heightMagicNumber * factor; 
	const float nPosY = nHeight;

	_name.setGeometry(QRect(nPosX, int(nPosY), nWidth, int(nHeight)));

	//Text and font
	float fontSize = (heightMagicNumber - 1) * factor;
	QFont f("Arial", int(fontSize), QFont::Bold);
  	_name.setFont(f);
	_name.setAlignment(Qt::AlignLeft);
	_name.setText(QString(_card->getName().c_str()));
}

void CardWidget::setPosition(const int xIndex, const LabelLocation location)
{
	//Geometry
	int xOffset = 0;
	int yOffset = 0;
	if(location == inHand)
	{
		xOffset = xIndex * (mWidth + mXHandOffSet);
		yOffset = mHeight + mYOffSet;
	}
	else if(location == inBoard)
	{
		xOffset = xIndex * (mWidth + mXBoardOffSet);
	}

	_xPos = startX + xOffset;
	_yPos = startY + yOffset;

	setGeometry(QRect(_xPos, _yPos, mWidth, mHeight));
	setLocation(location);
	refreshCardNameLabel();
	refreshCardCostLabel();
}

bool CardWidget::event(QEvent *myEvent)
{
	switch(myEvent->type())
	{        
	    case QEvent::MouseButtonRelease:
	    {
	    	_isSelected = true;
			emit cardWidgetClickedSignal();
	        break;     
	    }   
	    case QEvent::HoverEnter:
	    {
	        hoverEnter();
	        break;
	    }
		case QEvent::HoverLeave:
		{
	        hoverLeave();
	        break;
	    }
		case QEvent::HoverMove:
		{
	        hoverMove();
	        break;
	    }
	    default:
	    	break;
	}
	return QWidget::event(myEvent);
}

void CardWidget::hoverEnter()
{
	if(location() == inHand)
	{
		//State
		_isEnlarged = true;

		//Geometry
		const int mBigWidth = mWidth * mScaleFactor;
		const int mBigHeight = mHeight * mScaleFactor;

		setPixmap(_bckgndPix.scaled(mBigWidth, mBigHeight, Qt::KeepAspectRatio));
		setGeometry(QRect(_xPos, _yPos + mRaiseOffset, mBigWidth, mBigHeight));

		//Refresh text labels
	    refreshCardNameLabel();
	    refreshCardCostLabel();

	    //Display
		raise();
	}
}

void CardWidget::hoverLeave()
{
	if(location() == inHand)
	{
		//State
		_isEnlarged = false;

		//Geometry
		setPixmap(_bckgndPix.scaled(mWidth, mHeight, Qt::KeepAspectRatio));
		setGeometry(QRect(_xPos, _yPos, mWidth, mHeight));

		//Refresh text labels
	    refreshCardNameLabel();
	    refreshCardCostLabel();

	    //send signal
	    emit hoverLeaveSignal();
	}
}

void CardWidget::hoverMove()
{
	
}
