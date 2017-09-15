#ifndef FILERENAME_H
#define FILERENAME_H

#include <QWidget>

#include <QDir>
#include <QFileInfoList>
#include <QDragEnterEvent>

namespace Ui {
class FileRename;
}

class FileRename : public QWidget
{
    Q_OBJECT

public:
    explicit FileRename(QWidget *parent = 0);
    ~FileRename();

protected:
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragLeaveEvent(QDragLeaveEvent *event);
    virtual void dropEvent(QDropEvent *event);

private slots:
    void on_btn_old_clicked();

    void on_btn_rename_clicked();

    void on_lineEdit_new_textChanged(const QString &arg1);

private:
    Ui::FileRename *ui;

    QDir m_dir;
    QFileInfoList m_infoList;

    QString m_fileName;         //文件名
};

#endif // FILERENAME_H
