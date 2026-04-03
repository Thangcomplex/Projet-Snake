#include <iostream>
#include "snakebutton.hpp"
SnakeButton::SnakeButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent) {}

void SnakeButton::keyPressEvent(QKeyEvent *e)
{
    if (parent() != nullptr)
        QCoreApplication::sendEvent(parent(), e);
}
