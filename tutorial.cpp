#include "mainwindow.h"
#include <QMessageBox>
#include <QPixmap>

///////////////////////TUTORIAL///////////////////////

void MainWindow::on_actionTutorial_triggered()
{
    QMessageBox information;

    information.setTextFormat(Qt::RichText);   //this is what makes the links clickable
    information.setText(tr("<p align='left'><b>ubunsys</b></p></br>"
                  "<p align='left'>Recommended steps:</p></br>"
                  "<p align='left'>1. Push on 'Backup sudoers file'.</p></br>"
                  "<p align='left'>2. Then push on 'Enable sudo without pass'.</p></br>"
                  "<p align='left'>3. Install packages you want.</p></br>"
                  //"<p align='left'>\n</p></br>"
                  "<p align='left'>4. Execute all tweaks, system actions or reparations you want.</p></br>"));
    //ui->statusBar->showMessage(tr("Checking integrity system"));
    information.setWindowTitle(tr("Tutorial"));
    information.setStyleSheet("QLabel{width: 300px; min-width: 300px; max-width: 300px;}");
    information.setStandardButtons(QMessageBox::Ok);
    information.setIconPixmap(QPixmap(":/images/ubunsys.ico"));
    information.setWindowIcon(QIcon(":/images/ubunsys.ico"));
    information.setDefaultButton(QMessageBox::Ok);

    information.show();
    information.exec();
}
