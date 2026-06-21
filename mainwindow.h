#pragma once

#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSplitter>
#include <QToolBar>
#include <QStatusBar>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>

#include "University.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onAddStudent();
    void onRemoveStudent();
    void onAssignStudent();
    void refreshStudentTable();

    void onAddDormitory();
    void onAddRoom();
    void onDormSelected();
    void refreshDormList();

    void onSetMenu();
    void refreshMenuDisplay();

    void onSaveData();
    void onLoadData();

private:
    University    university;

    QTabWidget*   tabs         = nullptr;

    QTableWidget* studentTable = nullptr;
    QPushButton*  btnAddStu    = nullptr;
    QPushButton*  btnRemStu    = nullptr;
    QPushButton*  btnAssign    = nullptr;

    QListWidget*  dormList     = nullptr;
    QListWidget*  roomList     = nullptr;
    QPushButton*  btnAddDorm   = nullptr;
    QPushButton*  btnAddRoom   = nullptr;

    QLabel*       lblBreakfast = nullptr;
    QLabel*       lblLunch     = nullptr;
    QLabel*       lblDinner    = nullptr;
    QPushButton*  btnSetMenu   = nullptr;

    void setupUI();
    void setupToolbar();
    void setupStudentTab();
    void setupDormTab();
    void setupRestaurantTab();
};