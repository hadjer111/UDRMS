#include "MainWindow.h"
#include <memory>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    university("ENSIA")
{
    setWindowTitle("UDRMS - University Dormitory & Restaurant Management");
    resize(960, 640);
    setMinimumSize(720, 480);

    setupUI();
    setupToolbar();

    university.loadData("data/students.txt");

    refreshStudentTable();
    refreshDormList();
}

MainWindow::~MainWindow() {
    university.saveData("data/students.txt");
}


void MainWindow::setupUI() {
    tabs = new QTabWidget(this);
    setCentralWidget(tabs);

    setupStudentTab();
    setupDormTab();
    setupRestaurantTab();

    statusBar()->showMessage("Ready");
}

void MainWindow::setupToolbar() {
    QToolBar* toolbar = addToolBar("File");
    toolbar->setMovable(false);

    QAction* actSave = new QAction("Save Data", this);
    QAction* actLoad = new QAction("Load Data", this);

    toolbar->addAction(actSave);
    toolbar->addAction(actLoad);

    connect(actSave, &QAction::triggered, this, &MainWindow::onSaveData);
    connect(actLoad, &QAction::triggered, this, &MainWindow::onLoadData);
}


void MainWindow::setupStudentTab() {
    QWidget*     widget = new QWidget;
    QVBoxLayout* vbox   = new QVBoxLayout(widget);
    vbox->setContentsMargins(12, 12, 12, 12);
    vbox->setSpacing(8);

    studentTable = new QTableWidget(0, 4);
    studentTable->setHorizontalHeaderLabels({"Student ID", "Full Name", "Academic Year", "Assigned Dorm"});
    studentTable->horizontalHeader()->setStretchLastSection(true);
    studentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    studentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    studentTable->verticalHeader()->setVisible(false);
    studentTable->setAlternatingRowColors(true);

    btnAddStu = new QPushButton("Add Student");
    btnRemStu = new QPushButton("Remove Student");
    btnAssign = new QPushButton("Assign to Dorm");

    QHBoxLayout* btnRow = new QHBoxLayout;
    btnRow->addWidget(btnAddStu);
    btnRow->addWidget(btnRemStu);
    btnRow->addWidget(btnAssign);
    btnRow->addStretch();

    connect(btnAddStu, &QPushButton::clicked, this, &MainWindow::onAddStudent);
    connect(btnRemStu, &QPushButton::clicked, this, &MainWindow::onRemoveStudent);
    connect(btnAssign, &QPushButton::clicked, this, &MainWindow::onAssignStudent);

    vbox->addWidget(studentTable);
    vbox->addLayout(btnRow);

    tabs->addTab(widget, "Students");
}


void MainWindow::setupDormTab() {
    QWidget*     widget  = new QWidget;
    QVBoxLayout* vbox    = new QVBoxLayout(widget);
    vbox->setContentsMargins(12, 12, 12, 12);
    vbox->setSpacing(8);

    QSplitter* splitter = new QSplitter(Qt::Horizontal);

    QGroupBox*   leftBox = new QGroupBox("Dormitories");
    QVBoxLayout* leftL   = new QVBoxLayout(leftBox);
    dormList = new QListWidget;
    leftL->addWidget(dormList);

    QGroupBox*   rightBox = new QGroupBox("Rooms");
    QVBoxLayout* rightL   = new QVBoxLayout(rightBox);
    roomList = new QListWidget;
    rightL->addWidget(roomList);

    splitter->addWidget(leftBox);
    splitter->addWidget(rightBox);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);

    btnAddDorm = new QPushButton("Add Dormitory");
    btnAddRoom = new QPushButton("Add Room");

    QHBoxLayout* btnRow = new QHBoxLayout;
    btnRow->addWidget(btnAddDorm);
    btnRow->addWidget(btnAddRoom);
    btnRow->addStretch();

    connect(btnAddDorm, &QPushButton::clicked, this, &MainWindow::onAddDormitory);
    connect(btnAddRoom, &QPushButton::clicked, this, &MainWindow::onAddRoom);
    connect(dormList, &QListWidget::currentRowChanged, this, &MainWindow::onDormSelected);

    vbox->addWidget(splitter);
    vbox->addLayout(btnRow);

    tabs->addTab(widget, "Dormitories");
}


void MainWindow::setupRestaurantTab() {
    QWidget*     widget = new QWidget;
    QVBoxLayout* vbox   = new QVBoxLayout(widget);
    vbox->setContentsMargins(32, 24, 32, 24);
    vbox->setSpacing(16);

    QLabel* title = new QLabel("Today's Menu");
    QFont titleFont = title->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    title->setFont(titleFont);

    lblBreakfast = new QLabel("Not set");
    lblLunch     = new QLabel("Not set");
    lblDinner    = new QLabel("Not set");

    auto makeRow = [&](const QString& meal, QLabel* valueLabel) {
        QHBoxLayout* row   = new QHBoxLayout;
        QLabel*      fixed = new QLabel(meal + ":");
        fixed->setMinimumWidth(120);
        QFont f = fixed->font();
        f.setBold(true);
        fixed->setFont(f);
        row->addWidget(fixed);
        row->addWidget(valueLabel, 1);
        vbox->addLayout(row);
    };

    vbox->addWidget(title);
    vbox->addSpacing(8);
    makeRow("Breakfast", lblBreakfast);
    makeRow("Lunch",     lblLunch);
    makeRow("Dinner",    lblDinner);
    vbox->addSpacing(16);

    btnSetMenu = new QPushButton("Set Today's Menu");
    btnSetMenu->setFixedWidth(180);
    connect(btnSetMenu, &QPushButton::clicked, this, &MainWindow::onSetMenu);

    vbox->addWidget(btnSetMenu);
    vbox->addStretch();

    tabs->addTab(widget, "Restaurant");
}


void MainWindow::onAddStudent() {
    bool ok;
    QString id = QInputDialog::getText(this, "Add Student", "Student ID:",
                                       QLineEdit::Normal, "", &ok);
    if (!ok || id.trimmed().isEmpty()) return;

    if (university.findStudent(id.toStdString())) {
        QMessageBox::warning(this, "Duplicate ID",
                             "A student with ID " + id + " already exists.");
        return;
    }

    QString name = QInputDialog::getText(this, "Add Student", "Full Name:",
                                         QLineEdit::Normal, "", &ok);
    if (!ok || name.trimmed().isEmpty()) return;

    int year = QInputDialog::getInt(this, "Add Student", "Academic Year (1-5):",
                                    1, 1, 5, 1, &ok);
    if (!ok) return;

    university.addStudent(
        std::make_unique<Student>(id.toStdString(), name.toStdString(), year));

    refreshStudentTable();
    statusBar()->showMessage("Student added: " + name, 3000);
}

void MainWindow::onRemoveStudent() {
    int row = studentTable->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "No Selection", "Please click on a student row first.");
        return;
    }

    QString id = studentTable->item(row, 0)->text();
    auto reply = QMessageBox::question(this, "Confirm Delete",
                                       "Remove student with ID: " + id + "?",
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) return;

    university.removeStudent(id.toStdString());
    refreshStudentTable();
    statusBar()->showMessage("Student removed.", 3000);
}

void MainWindow::onAssignStudent() {
    int row = studentTable->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "No Selection", "Select a student first.");
        return;
    }

    QString studentId = studentTable->item(row, 0)->text();

    QStringList dormNames;
    for (auto& d : university.getDormitories())
        dormNames << QString::fromStdString(d->getName());

    if (dormNames.isEmpty()) {
        QMessageBox::warning(this, "No Dormitories", "Add a dormitory before assigning students.");
        return;
    }

    bool ok;
    QString dormName = QInputDialog::getItem(this, "Assign to Dormitory",
                                             "Select dormitory:",
                                             dormNames, 0, false, &ok);
    if (!ok) return;

    int roomNum = QInputDialog::getInt(this, "Assign to Room", "Room number:",
                                       101, 1, 9999, 1, &ok);
    if (!ok) return;

    bool success = university.assignStudentToDorm(
        studentId.toStdString(), dormName.toStdString(), roomNum);

    if (success) {
        refreshStudentTable();
        refreshDormList();
        statusBar()->showMessage("Student assigned to room " + QString::number(roomNum), 3000);
    } else {
        QMessageBox::warning(this, "Assignment Failed", "Room is full or room number not found.");
    }
}

void MainWindow::refreshStudentTable() {
    auto& studs = university.getStudents();
    studentTable->setRowCount((int)studs.size());

    for (int i = 0; i < (int)studs.size(); ++i) {
        Student* s = studs[i].get();

        studentTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(s->getId())));
        studentTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(s->getFullName())));
        studentTable->setItem(i, 2, new QTableWidgetItem(QString::number(s->getAcademicYear())));

        QString dormName = "-";
        for (auto& d : university.getDormitories())
            for (auto& room : d->getRooms())
                if (room.hasStudent(s->getId()))
                    dormName = QString::fromStdString(d->getName());

        studentTable->setItem(i, 3, new QTableWidgetItem(dormName));
    }
    studentTable->resizeColumnsToContents();
}

void MainWindow::onAddDormitory() {
    bool ok;
    QString name = QInputDialog::getText(this, "Add Dormitory", "Dormitory name:",
                                         QLineEdit::Normal, "", &ok);
    if (!ok || name.trimmed().isEmpty()) return;

    int cap = QInputDialog::getInt(this, "Add Dormitory", "Total capacity:",
                                   100, 1, 9999, 1, &ok);
    if (!ok) return;

    QString restName = QInputDialog::getText(this, "Add Dormitory", "Restaurant name:",
                                             QLineEdit::Normal, name + " Cafeteria", &ok);
    if (!ok) return;

    university.addDormitory(std::make_unique<Dormitory>(
        name.toStdString(), cap, restName.toStdString()));

    refreshDormList();
    statusBar()->showMessage("Dormitory added: " + name, 3000);
}

void MainWindow::onAddRoom() {
    int idx = dormList->currentRow();
    if (idx < 0) {
        QMessageBox::information(this, "No Dorm Selected", "Click on a dormitory first.");
        return;
    }

    bool ok;
    int roomNum = QInputDialog::getInt(this, "Add Room", "Room number:",
                                       101, 1, 9999, 1, &ok);
    if (!ok) return;

    int cap = QInputDialog::getInt(this, "Add Room", "Room capacity:",
                                   2, 1, 8, 1, &ok);
    if (!ok) return;

    university.getDormitories()[idx]->addRoom(Room(roomNum, cap));
    onDormSelected();
    statusBar()->showMessage("Room " + QString::number(roomNum) + " added.", 3000);
}

void MainWindow::onDormSelected() {
    roomList->clear();
    int idx = dormList->currentRow();
    if (idx < 0) return;

    Dormitory* dorm = university.getDormitories()[idx].get();
    for (const auto& room : dorm->getRooms()) {
        QString label = QString("Room %1  [%2/%3]%4")
        .arg(room.getRoomNumber())
            .arg(room.getOccupancy())
            .arg(room.getCapacity())
            .arg(room.isFull() ? "  FULL" : "");
        roomList->addItem(label);
    }
}

void MainWindow::refreshDormList() {
    dormList->clear();
    for (auto& d : university.getDormitories()) {
        QString label = QString::fromStdString(d->getName())
        + QString("  (%1 students)").arg(d->getTotalStudents());
        dormList->addItem(label);
    }
}

void MainWindow::onSetMenu() {
    if (university.getDormitories().empty()) {
        QMessageBox::warning(this, "No Dormitory", "Add a dormitory before setting a menu.");
        return;
    }

    Restaurant& rest = university.getDormitories()[0]->getRestaurant();
    bool ok;

    QString b = QInputDialog::getText(this, "Set Menu", "Breakfast:",
                                      QLineEdit::Normal,
                                      QString::fromStdString(rest.getBreakfast()), &ok);
    if (!ok) return;

    QString l = QInputDialog::getText(this, "Set Menu", "Lunch:",
                                      QLineEdit::Normal,
                                      QString::fromStdString(rest.getLunch()), &ok);
    if (!ok) return;

    QString d = QInputDialog::getText(this, "Set Menu", "Dinner:",
                                      QLineEdit::Normal,
                                      QString::fromStdString(rest.getDinner()), &ok);
    if (!ok) return;

    rest.setMenu(b.toStdString(), l.toStdString(), d.toStdString());
    refreshMenuDisplay();
    statusBar()->showMessage("Menu updated.", 3000);
}

void MainWindow::refreshMenuDisplay() {
    if (university.getDormitories().empty()) return;

    const Restaurant& rest = university.getDormitories()[0]->getRestaurant();

    auto setLabel = [](QLabel* lbl, const std::string& val) {
        if (val.empty()) {
            lbl->setText("Not set");
            lbl->setStyleSheet("color: grey; font-style: italic;");
        } else {
            lbl->setText(QString::fromStdString(val));
            lbl->setStyleSheet("");
        }
    };

    setLabel(lblBreakfast, rest.getBreakfast());
    setLabel(lblLunch,     rest.getLunch());
    setLabel(lblDinner,    rest.getDinner());
}

void MainWindow::onSaveData() {
    university.saveData("data/students.txt");
    QMessageBox::information(this, "Saved", "Data saved to data/students.txt");
    statusBar()->showMessage("Data saved.", 3000);
}

void MainWindow::onLoadData() {
    university.loadData("data/students.txt");
    refreshStudentTable();
    refreshDormList();
    statusBar()->showMessage("Data loaded.", 3000);
}