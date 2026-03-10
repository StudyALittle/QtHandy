#include "qhbasepopupcontent.h"

QhBasePopupContent::QhBasePopupContent(QWidget *parent):
    QWidget(parent)
{

}

QhBasePopup *QhBasePopupContent::basePopup()
{
    return m_qBasePopup;
}

bool QhBasePopupContent::afterButtonOk()
{
    return true;
}

bool QhBasePopupContent::afterButtonCancel()
{
    return true;
}

bool QhBasePopupContent::afterButtonClose()
{
    return true;
}

void QhBasePopupContent::setBasePopup(QhBasePopup *basePopup)
{
    m_qBasePopup = basePopup;
}
