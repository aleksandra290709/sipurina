#include "inorder.h"

Inorder::Inorder(QObject *parent) :
    VisualTree()
{
    setParent(parent);
    m_animationInitialized= false;
}

void Inorder::initializeAnimation()
{
    //    Init explanation text:
        if (m_explanationText) {
            m_explanationText->setPlainText("Nodes are reached in order: ");
        }
        else {
            m_explanationText = new QGraphicsTextItem("Nodes are reached in order: ");
            addItem(m_explanationText);
        }
        m_explanationText->setFont(QFont("Arial", 14, -1));
        m_explanationText->setPos(0,height()-m_explanationText->boundingRect().height());

    obidji_lkd(getRoot());

//    Initializing variables for animation control:
    m_animationInitialized= true;
    m_currentStepInAnimation= 0;
    m_numberOfStepsInAnimation= m_operations.size();
}

void Inorder::obidji_lkd(VisualTreeElement* e){
    if(e){
        obidji_lkd(e->getLeft());

        m_operations.push_back([=, this] () {
            emit highlightLine(3);
            QString order;
//            If animation is going forward:
            if (isGoingForward()) {
                if (e != getRoot()->nadji_minimum(getRoot(), 5000))//control coma (don't wanna : , first_reached)
                    m_explanationText->setPlainText(QString(m_explanationText->toPlainText()) + ", "+ QString::number(e->getValue()));
                else
                    m_explanationText->setPlainText(QString(m_explanationText->toPlainText()) + QString::number(e->getValue()));
            }
//            Animation going backward:
            else {
                order= m_explanationText->toPlainText();
                if (e != getRoot())
                    order= order.mid(0, order.lastIndexOf(","));
                else
                    order= "Nodes are reached in order: ";
                m_explanationText->setPlainText(order);
            }

            visit_node(e);
        });


        obidji_lkd(e->getRight());
}
}

QHBoxLayout* Inorder::returnControls()
{
    return 0;
}
