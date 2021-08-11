#include <algorithm>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plant.h"
#include "mouse.h"
#include "snake.h"
#include "lynx.h"
#include "cheetah.h"
#include "vulture.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap bkgnd("D:/Qt progs/ImitationModel/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    setWindowIcon(QIcon("D:/Qt progs/ImitationModel/icon.jpg"));

    ui->nextButton->setVisible(false);
    ui->startButton->setVisible(false);
    ui->spinBox->setVisible(false);
    ui->timerLabel->setVisible(false);
    ui->backButton->setVisible(false);


    ui->ChooseCountLabel->setVisible(false);
    ui->PlantCountLabel->setVisible(false);
    ui->PlantCountSpinBox->setVisible(false);
    ui->MouseCountLabel->setVisible(false);
    ui->MouseCountSpinBox->setVisible(false);
    ui->SnakeCountLabel->setVisible(false);
    ui->SnakeCountSpinBox->setVisible(false);
    ui->LynxCountLabel->setVisible(false);
    ui->LynxCountSpinBox->setVisible(false);
    ui->CheetahCountLabel->setVisible(false);
    ui->CheetahCountSpinBox->setVisible(false);
    ui->VultureCountLabel->setVisible(false);
    ui->VultureCountSpinBox->setVisible(false);

    map->randomGenerate(20, 5, 4, 2, 1, 3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.eraseRect(0, 0, 952, 872);
    painter.drawRect(0, 0, cellSize * map->getWidth(), cellSize * map->getHeight());
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::transparent);
    /* Рисование сетки. */
    int x1 = 0;		// Начальная x координата сетки
    int x2 = cellSize * map->getWidth(); // Конечная x координата сетки.
    int y1 = cellSize;		// Начальная y координата сетки.
    int y2 = cellSize;		// Конечная y координата сетки.
    // Рисование горизонатльных линий сетки.
    for (int i = 1; i < map->getHeight(); i++)
    {
        painter.drawLine(x1, y1, x2, y2);
        y1 += cellSize;
        y2 += cellSize;
    }
    y1 = 0;
    y2 = cellSize * map->getHeight();
    x1 = cellSize;
    x2 = cellSize;
    // Рисование вертикальных линий сетки.
    for (int i = 1; i < map->getWidth(); i++)
    {
        painter.drawLine(x1, y1, x2, y2);
        x1 += cellSize;
        x2 += cellSize;
    }

    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);

    painter.setPen(Qt::black);
    painter.setBrush(QColor(130, 130, 130));
    painter.drawEllipse(3, (cellSize * map->getHeight() + 15), animalSize * 3, animalSize * 3);
    painter.drawText(animalSize * 3 + 8, (cellSize * map->getHeight() + 12 + animalSize * 3), "- Мышь");
    painter.setBrush(QColor(52, 178, 51));
    painter.drawEllipse(3, (cellSize * map->getHeight() + 40), animalSize * 3, animalSize * 3);
    painter.drawText(animalSize * 3 + 8, (cellSize * map->getHeight() + 37 + animalSize * 3), "- Змея");
    painter.setBrush(QColor(232, 142, 90));
    painter.drawEllipse(3, (cellSize * map->getHeight() + 65), animalSize * 3, animalSize * 3);
    painter.drawText(animalSize * 3 + 8, (cellSize * map->getHeight() + 62 + animalSize * 3), "- Рысь");
    painter.setBrush(QColor(190, 79, 26));
    painter.drawEllipse(3, (cellSize * map->getHeight() + 90), animalSize * 3, animalSize * 3);
    painter.drawText(animalSize * 3 + 8, (cellSize * map->getHeight() + 87 + animalSize * 3), "- Леопард");
    painter.setBrush(QColor(153, 102, 204));
    painter.drawEllipse(3, (cellSize * map->getHeight() + 115), animalSize * 3, animalSize * 3);
    painter.drawText(animalSize * 3 + 8, (cellSize * map->getHeight() + 112 + animalSize * 3), "- Стервятник");
    painter.setBrush(Qt::green);
    painter.drawRect(3, (cellSize * map->getHeight() + 142), animalSize * 3, animalSize * 3);
    painter.drawText(animalSize * 3 + 8, (cellSize * map->getHeight() + 137 + animalSize * 3), "- Трава");

    /* Рисование объектов. */
    pen.setWidth(3);
    QColor* color = new QColor(0, 0, 0);;
    std::list<ObjectOnMap*> allObjects = map->getAllObjects();
    for (std::list <ObjectOnMap*>::iterator obj = allObjects.begin(); obj != allObjects.end(); ++obj)
    {
        if (!dynamic_cast<Plant*>(*obj))
        {
            if ((*obj)->isAlive())
            {
                if (dynamic_cast<Mouse*>(*obj))
                    color = new QColor(130, 130, 130);
                else if (dynamic_cast<Snake*>(*obj))
                    color = new QColor(52, 178, 51);
                else if (dynamic_cast<Lynx*>(*obj))
                    color = new QColor(232, 142, 90);
                else if (dynamic_cast<Cheetah*>(*obj))
                    color = new QColor(190, 79, 26);
                else if (dynamic_cast<Vulture*>(*obj))
                    color = new QColor(153, 102, 204);
            }
            else if ((*obj)->hasMeat())
                color = new QColor(0, 0, 0);
            else
                continue;
            painter.setPen(*color);
            painter.setBrush(*color);
            if ((*obj)->isAlive())
                painter.drawEllipse((*obj)->get_xCoord() * cellSize, (*obj)->get_yCoord() * cellSize, animalSize, animalSize);
            else
                painter.fillRect((*obj)->get_xCoord() * cellSize, (*obj)->get_yCoord() * cellSize, animalSize+3, animalSize+3, Qt::black);
            if ((*obj)->isAlive())
            {
                 if((*obj)->getSatietyPoints() <= 0)
                     pen.setDashPattern({0.0, 4.0, 1.0, 4.0});
            pen.setColor(*color);
            painter.setBrush(Qt::transparent);
            painter.setPen(pen);
            painter.drawEllipse(((*obj)->get_xCoord() - (*obj)->getSightRadius()) * cellSize,
                       ((*obj)->get_yCoord() - (*obj)->getSightRadius()) * cellSize, 2 * (*obj)->getSightRadius() * cellSize,
                                2 * (*obj)->getSightRadius() *cellSize);
            pen.setDashPattern({1});
            }

            painter.setBrush(Qt::black);
        }
        else
        {
            if ((*obj)->getVolume() > 0)
                painter.fillRect((*obj)->get_xCoord() * cellSize+1, (*obj)->get_yCoord() * cellSize+1, cellSize-1, cellSize-1, Qt::green);
            else
                continue;
            painter.setBrush(Qt::black);
        }
    }
}


void MainWindow::on_stepModeButton_clicked()
{
    ui->stepModeButton->setDisabled(true);
    ui->regularModeButton->setDisabled(true);
    ui->nextButton->setVisible(true);
    ui->backButton->setVisible(true);
}


void MainWindow::on_nextButton_clicked()
{
    map->liveStep();
    repaint();
}

void MainWindow::on_regularModeButton_clicked()
{
    timer = new QTimer();
    ui->stepModeButton->setDisabled(true);
    ui->regularModeButton->setDisabled(true);
    ui->startButton->setDisabled(false);
    ui->spinBox->setVisible(true);
    ui->startButton->setVisible(true);
    ui->timerLabel->setVisible(true);
    ui->backButton->setVisible(true);
}

void MainWindow::on_backButton_clicked()
{
    ui->stepModeButton->setDisabled(false);
    ui->regularModeButton->setDisabled(false);
    ui->spinBox->setVisible(false);
    ui->startButton->setVisible(false);
    ui->timerLabel->setVisible(false);
    ui->nextButton->setVisible(false);
    ui->backButton->setVisible(false);
    timer->stop();
}

void MainWindow::on_startButton_clicked()
{
    ui->startButton->setDisabled(true);
    long unsigned stepDelayMSeconds = ui->spinBox->value();;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMapByTimer()));
    timer->start(stepDelayMSeconds);
}

void MainWindow::updateMapByTimer()
{
    map->liveStep();
    repaint();
}


void MainWindow::on_restartButton_clicked()
{
    if (ui->restartButton->text() == "Создать новую\nимитацию")
    {
        ui->restartButton->setText("Подтвердить");
        ui->ChooseCountLabel->setVisible(true);
        ui->PlantCountLabel->setVisible(true);
        ui->PlantCountSpinBox->setVisible(true);
        ui->MouseCountLabel->setVisible(true);
        ui->MouseCountSpinBox->setVisible(true);
        ui->SnakeCountLabel->setVisible(true);
        ui->SnakeCountSpinBox->setVisible(true);
        ui->LynxCountLabel->setVisible(true);
        ui->LynxCountSpinBox->setVisible(true);
        ui->CheetahCountLabel->setVisible(true);
        ui->CheetahCountSpinBox->setVisible(true);
        ui->VultureCountLabel->setVisible(true);
        ui->VultureCountSpinBox->setVisible(true);
    }
    else
    {
        ui->restartButton->setText("Создать новую\nимитацию");
        ui->ChooseCountLabel->setVisible(false);
        ui->PlantCountLabel->setVisible(false);
        ui->PlantCountSpinBox->setVisible(false);
        ui->MouseCountLabel->setVisible(false);
        ui->MouseCountSpinBox->setVisible(false);
        ui->SnakeCountLabel->setVisible(false);
        ui->SnakeCountSpinBox->setVisible(false);
        ui->LynxCountLabel->setVisible(false);
        ui->LynxCountSpinBox->setVisible(false);
        ui->CheetahCountLabel->setVisible(false);
        ui->CheetahCountSpinBox->setVisible(false);
        ui->VultureCountLabel->setVisible(false);
        ui->VultureCountSpinBox->setVisible(false);

        map = new Map(50, 50);
        map->randomGenerate(ui->PlantCountSpinBox->value(), ui->MouseCountSpinBox->value(),
                            ui->SnakeCountSpinBox->value(), ui->LynxCountSpinBox->value(),
                            ui->CheetahCountSpinBox->value(), ui->VultureCountSpinBox->value());
        repaint();
    }
}

