#ifndef SNAKEBUTTON_HPP
#define SNAKEBUTTON_HPP

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.hpp"

class SnakeButton : public QPushButton
{

public:
    explicit SnakeButton (const QString &texte, QWidget *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *e) override;
};

#endif // SNAKEBUTTON_HPP

