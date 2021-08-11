#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include "map.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/* Класс Главное Окно. */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    // Карта 50 клеток на 50.
    Map* map = new Map(50, 50);
    // Размер клетки - 14 пикселей.
    const int cellSize = 14;
    // Размер животного - 7 пикселей.
    const int animalSize = 7;
protected:
    // Таймер.
    QTimer* timer = new QTimer();
    // Метод для рисования карты и объектов на ней.
    void paintEvent(QPaintEvent *) override;
private slots:
    // Метод обработки нажатия на кнопку "По шагам".
    void on_stepModeButton_clicked();
    // Метод обработки нажатия на кнопку "Далее".
    void on_nextButton_clicked();
    // Метод обработки нажатия на кнопку "Начать имитацию".
    void on_startButton_clicked();
    // Метод обработки нажатия на кнопку "Обычный режим работы".
    void on_regularModeButton_clicked();
    // Метод обработки нажатия на кнопку "Назад".
    void on_backButton_clicked();
    // Метод обработки обновления карты после тика таймера.
    void updateMapByTimer();
    // Метод обработки нажатия на кнопку "Создать новую имитацию".
    void on_restartButton_clicked();
};
#endif // MAINWINDOW_H
