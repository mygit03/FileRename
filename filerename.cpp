#include "filerename.h"
#include "ui_filerename.h"

#include <QHeaderView>
#include <QFileDialog>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDebug>

FileRename::FileRename(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileRename)
{
    ui->setupUi(this);

    setWindowTitle(tr("文件重命名"));
    setWindowIcon(QIcon(":/image/video.png"));

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setEditTriggers(QHeaderView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);                 //最后一列宽度自适应
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch) ;   //宽度自适应

    QStringList headers;
    headers.clear();
    headers << tr("原文件名") << tr("新文件名");
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    ui->lineEdit_old->setReadOnly(true);

    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FileRename::~FileRename()
{
    delete ui;
}

void FileRename::on_btn_old_clicked()
{
    QString path = ui->lineEdit_old->text();
    if(path.isEmpty()){
        path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    }
    QString dir = QFileDialog::getExistingDirectory(this, tr("文件目录"), path, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_old->setText(dir);

    m_dir.setPath(dir);
    m_dir.setFilter(QDir::Files | QDir::NoSymLinks);
    ui->lineEdit_new->setPlaceholderText(m_dir.dirName());

    QStringList filters;
    filters<<QString("*.mkv")<<QString("*.mp4")<<QString("*.avi")<<QString("*.rmvb");
    m_dir.setNameFilters(filters);
    m_infoList = m_dir.entryInfoList();

    ui->tableWidget->setRowCount(m_infoList.size());

    for(int row = 0; row < m_infoList.size(); ++row){
        QTableWidgetItem *item = new QTableWidgetItem(m_infoList.at(row).fileName());
        ui->tableWidget->setItem(row, 0, item);
    }
}

void FileRename::on_btn_rename_clicked()
{
    QString name = ui->lineEdit_new->text();
    if(name.isEmpty()){
        name = ui->lineEdit_new->placeholderText();
    }

    QFileInfo info;
    QFile file;
    for(int i = 0; i < m_infoList.size(); ++i){
        info = m_infoList.at(i);
        file.setFileName(info.absoluteFilePath());

        QString newName = info.path().append("/" + name);
        newName.append(QString("%1").arg(i+1,2,10,QLatin1Char('0')) + "."); //编号 十进制补零
        newName.append(info.suffix());                                      //文件名后缀
        file.rename(info.absoluteFilePath(), newName);
    }

    m_dir.refresh();
    m_infoList = m_dir.entryInfoList();
    QStringList fileList = m_dir.entryList();
    qDebug() << fileList;
    for(int row = 0; row < m_infoList.size(); ++row){
        QTableWidgetItem *item = new QTableWidgetItem(m_infoList.at(row).fileName());
        ui->tableWidget->setItem(row, 1, item);
    }
}

void FileRename::on_lineEdit_new_textChanged(const QString &arg1)
{
    for(int row = 0; row < m_infoList.size(); ++row){
        QTableWidgetItem *item = ui->tableWidget->item(row, 0);
        item->setText(m_infoList.at(row).fileName());
        ui->tableWidget->setItem(row, 0, item);
    }
}
