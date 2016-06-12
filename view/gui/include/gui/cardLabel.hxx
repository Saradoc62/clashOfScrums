#ifndef CARDLABEL_HXX
#define CARDLABEL_HXX

#include <QtGui/QLabel>

#include <model/card.hxx>

class CardLabel : public QLabel
{
Q_OBJECT

public:
    CardLabel(const Card* card, QWidget* pParent = 0);
    virtual ~CardLabel();

    //getters
    const bool isSelected() const {return _isSelected;}

    void setPosition(const int pos);

signals:
	void cardLabelClickedSignal();	

public slots:
    void cardLabelSelected();

protected:
	 bool event(QEvent *myEvent);

private:
    void fillCardLabel(const Card* card);

    bool _isSelected;

};

#endif //CARDLABEL_HXX
