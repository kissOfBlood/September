#include "septembereditor.h"
#include "ui_septembereditor.h"

SeptemberEditor::SeptemberEditor(QWidget* parent) : QMainWindow(parent),
    ui(new Ui::SeptemberEditor)
{
    ui->setupUi(this);
    ui->widgetSearchAndReplace->setVisible(false);
    ui->widgetCreateWidget->setVisible(false);
    ui->widgetOpenUI->setVisible(false);
    ui->listDocument->setVisible(false);
    ui->mnNew->setShortcut(QKeySequence::New);
    ui->mnOpen->setShortcut(QKeySequence::Open);
    ui->mnQuit->setShortcut(QKeySequence::Quit);

    ui->mnUndo->setShortcut(QKeySequence::Undo);
    ui->mnRedo->setShortcut(QKeySequence::Redo);
    ui->mnCut->setShortcut(QKeySequence::Cut);
    ui->mnCopy->setShortcut(QKeySequence::Copy);
    ui->mnPaste->setShortcut(QKeySequence::Paste);
    ui->mnSelectAll->setShortcut(QKeySequence::SelectAll);
    ui->mnSearchReplace->setShortcut(QKeySequence::Find);

    ui->mnListDocument->setCheckable(true);
    ui->mnCreateWidget->setCheckable(true);
    ui->mnOpenUi->setCheckable(true);
    ui->mnNumberLine->setCheckable(true);
    ui->mnNumberLine->setChecked(true);
    ui->mnNumberLine->setShortcut(Qt::CTRL + Qt::Key_L);
    ui->mnListDocument->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_Q);
    ui->mnCreateWidget->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_W);
    ui->mnOpenUi->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_E);
    ui->mnZoomIn->setShortcut(QKeySequence::ZoomIn);
    ui->mnZoomOut->setShortcut(QKeySequence::ZoomOut);

    this->connect(ui->btnCloseListFile,     &QPushButton::clicked, this, &SeptemberEditor::closeOrShowListFile);
    this->connect(ui->btnSearchAndReplace,  &QPushButton::clicked, this, &SeptemberEditor::closeOrShowWidgetSearchAndReplace);
    this->connect(ui->btnCreateWidget,      &QPushButton::clicked, this, &SeptemberEditor::closeOrShowCreateWidget);
    this->connect(ui->btnOpenUi,            &QPushButton::clicked, this, &SeptemberEditor::closeOrShowOpenUI);
    this->connect(ui->barBtnOpenFile,       &QPushButton::clicked, this, &SeptemberEditor::openFile);
    this->connect(ui->mnOpen,           &QAction::triggered,    this, &SeptemberEditor::openFile);
    this->connect(ui->mnQuit,           &QAction::triggered,    qApp, &QApplication::quit);
    this->connect(ui->mnUndo,           &QAction::triggered,    ui->plainTextEdit, &CoreEditor::undo);
    this->connect(ui->mnRedo,           &QAction::triggered,    ui->plainTextEdit, &CoreEditor::redo);
    this->connect(ui->mnCut,            &QAction::triggered,    ui->plainTextEdit, &CoreEditor::cut);
    this->connect(ui->mnCopy,           &QAction::triggered,    ui->plainTextEdit, &CoreEditor::copy);
    this->connect(ui->mnPaste,          &QAction::triggered,    ui->plainTextEdit, &CoreEditor::paste);
    this->connect(ui->mnSelectAll,      &QAction::triggered,    ui->plainTextEdit, &CoreEditor::selectAll);
    this->connect(ui->mnSearchReplace,  &QAction::triggered,    this, &SeptemberEditor::closeOrShowWidgetSearchAndReplace);
    this->connect(ui->mnListDocument, &QAction::triggered, std::bind(&SeptemberEditor::closeOrShowListFile, this));
    this->connect(ui->mnCreateWidget, &QAction::triggered, std::bind(&SeptemberEditor::closeOrShowCreateWidget, this));
    this->connect(ui->mnOpenUi,       &QAction::triggered, std::bind(&SeptemberEditor::closeOrShowOpenUI, this));
    this->connect(ui->mnNumberLine,   &QAction::triggered, ui->plainTextEdit, &CoreEditor::setVisibleLineNimberArea);
    this->connect(ui->mnZoomIn,     &QAction::triggered, ui->plainTextEdit, &CoreEditor::zoomDocIn);
    this->connect(ui->mnZoomOut,    &QAction::triggered, ui->plainTextEdit, &CoreEditor::zoomDocOut);

    this->connect(ui->plainTextEdit, &CoreEditor::textChanged, this, [this]()
    { emit updateStyleSheet(ui->plainTextEdit->document()->toPlainText()); });
}

SeptemberEditor::~SeptemberEditor()
{ delete ui; }

QString SeptemberEditor::styleSheet() const
{ return ui->plainTextEdit->document()->toPlainText(); }

QTextDocument* SeptemberEditor::getDocument() const
{ return ui->plainTextEdit->document(); }

void SeptemberEditor::setPositionCursor(const QTextCursor& cursor)
{ ui->plainTextEdit->setTextCursor(cursor); }

void SeptemberEditor::closeOrShowListFile()
{
    QPushButton* button = qobject_cast<QPushButton*>(this->sender());
    static bool clicked = false;
    if(clicked)
    {
        if(button != nullptr)
            ui->mnListDocument->setChecked(false);

        clicked = false;
        ui->listDocument->setVisible(false);
    }
    else
    {
        if(button != nullptr)
            ui->mnListDocument->setChecked(true);

        clicked = true;
        ui->listDocument->setVisible(true);
    }
}

void SeptemberEditor::closeOrShowWidgetSearchAndReplace()
{
    if(m_clickedButton.searchAndReplace)
    {
        m_clickedButton.searchAndReplace = false;
        ui->widgetSearchAndReplace->setVisible(false);
        ui->plainTextEdit->setFocus();
    }
    else
    {
        m_clickedButton.searchAndReplace = true;
        m_clickedButton.createWidget = false;
        m_clickedButton.openUI = false;
        ui->btnOpenUi->setDown(false);
        ui->widgetCreateWidget->setVisible(false);
        ui->widgetOpenUI->setVisible(false);
        ui->widgetSearchAndReplace->setVisible(true);
        ui->widgetSearchAndReplace->setFocusEditSearch();
        ui->mnCreateWidget->setChecked(false);
        ui->mnOpenUi->setChecked(false);
    }
}

void SeptemberEditor::closeOrShowCreateWidget()
{
    QPushButton* button = qobject_cast<QPushButton*>(this->sender());
    if(m_clickedButton.createWidget)
    {
        if(button != nullptr)
            ui->mnCreateWidget->setChecked(false);

        m_clickedButton.createWidget = false;
        ui->widgetCreateWidget->setVisible(false);
    }
    else
    {
        if(button == nullptr)
            ui->mnOpenUi->setChecked(false);
        else
        {
            ui->mnCreateWidget->setChecked(true);
            ui->mnOpenUi->setChecked(false);
        }
        m_clickedButton.createWidget = true;
        m_clickedButton.searchAndReplace = false;
        m_clickedButton.openUI = false;
        ui->widgetSearchAndReplace->setVisible(false);
        ui->widgetOpenUI->setVisible(false);
        ui->widgetCreateWidget->setVisible(true);
    }
}

void SeptemberEditor::closeOrShowOpenUI()
{
    QPushButton* button = qobject_cast<QPushButton*>(this->sender());
    if(m_clickedButton.openUI)
    {
        if(button != nullptr)
            ui->mnOpenUi->setChecked(false);

        m_clickedButton.openUI = false;
        ui->widgetOpenUI->setVisible(false);
    }
    else
    {
        if(button == nullptr)
            ui->mnCreateWidget->setChecked(false);
        else
        {
            ui->mnOpenUi->setChecked(true);
            ui->mnCreateWidget->setChecked(false);
        }
        m_clickedButton.openUI = true;
        m_clickedButton.searchAndReplace = false;
        m_clickedButton.createWidget = false;
        ui->widgetSearchAndReplace->setVisible(false);
        ui->widgetCreateWidget->setVisible(false);
        ui->widgetOpenUI->setVisible(true);
    }
}

void SeptemberEditor::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, QString("Open file"), QString(), QString("*.qss"));
    if(path.length() == 0)
        return;

    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText(file.readAll());
    }
    file.close();
    QTextCursor cursorFirst(ui->plainTextEdit->document());
    cursorFirst.setPosition(0);
    ui->plainTextEdit->setTextCursor(cursorFirst);
}
