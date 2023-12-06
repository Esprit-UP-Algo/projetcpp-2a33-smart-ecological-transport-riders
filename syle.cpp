#include "syle.h"


void applyStyles(Ui::interface1 *ui)
{
    QString button1_style =
        "QPushButton {"
        "    background-color: #426e42;"  // Background color
        "    color: #ffffff;"              // Text color
        "    padding: 5px 10px;"           // Padding around text
        "    font-size: 20px;"             // Font size
        "    border: 1px solid #153015;"   // Border color
        "    border-radius: 5px;"          // Border radius for rounded corners
        "}"
        ""
        "QPushButton:hover {"
        "    background-color: #6aa36a;"  // Background color on hover
        "    border: 1px solid #193619;"   // Border color on hover
        "}"
        ""
        "QPushButton:pressed {"
        "    background-color: #6aa36a;"  // Background color when pressed
        "    border: 1px solid #193619;"   // Border color when pressed
        "}";

    QString combobox_style =
        "QComboBox {"
        "    background-color: #4b6e4b;"  // Background color
        "    color: #4b6e4b;"              // Text color
        "    border: 1px solid #0d380d;"   // Border color
        "    border-radius: 5px;"          // Border radius for rounded corners
        "    padding: 3px 8px;"            // Padding around text
        "    selection-background-color: #498249;"  // Background color when an item is selected
        "}"
        ""
        "QComboBox::drop-down {"
        "    border: none;"  // Remove the default drop-down arrow
        "}"
        ""
        "QComboBox::down-arrow {"
        "    image: url(:/path/to/down_arrow.png);"  // Replace with your own image for the drop-down arrow
        "}";

    QString lineEdit_style =
        "QLineEdit {"
        "    background-color: #a2dba2;"
        "    border: 1px solid #304530;"
        "    padding: 5px;"
        "    color: #004C46;"
        "    border-radius: 10px;"
        "}"
        ""
        "QLineEdit:hover {"
        "    border: 1px solid #307830;"
        "}"
        ""
        "QLineEdit:focus {"
        "    border: 2px solid #307830;"
        "}";

    QString group_box_style =
        "QGroupBox {"
        "    border: 2px solid #437054;"  // Border color and width
        "    border-radius: 5px;"          // Border radius for rounded corners
        "    margin-top: 10px;"            // Top margin
        "}"
        ""
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"   // Ensure the title is inside the border
        "    subcontrol-position: top left;"  // Position the title at the top left
        "    padding: 5px 10px;"            // Padding around the title
        "    color: #ffffff;"               // Text color of the title
        "    background-color: #548767;"    // Background color of the title
        "    border: 1px solid #395e47;"    // Border color of the title
        "    border-top-left-radius: 4px;"  // Border radius for the top-left corner of the title
        "    border-top-right-radius: 4px;" // Border radius for the top-right corner of the title
        "}";

    QString tabWidget_style =
        "QTabWidget::pane {"
        "    border: 1px solid #437054;" // Border color
        "}"
        ""
        "QTabBar::tab {"
        "    background-color: #437054;"   // Updated background color of tabs
        "    color: #ffffff;"               // Text color of tabs
        "    padding: 12px 18px;"
        "    border-top-left-radius: 10px;"   // Set the radius for the top-left corner
        "    border-top-right-radius: 10px;"  // Set the radius for the top-right corner
        "}"
        ""
        "QTabBar::tab:selected {"
        "    background-color: #1c3d29;" // Background color of the selected tab
        "}"
        ""
        "QTabBar::tab:hover {"
        "    background-color: #1c3d29;" // Background color when hovering over a tab
        "}";
    QString tableStyle =
            "QTableWidget {"
            "    background-color: #c2edd3;"      // Background color
            "    color: #ffffff;"                  // Text color
            "    border: 1px solid #144026;"       // Border color
            "    border-radius: 5px;"              // Border radius for rounded corners
            "}"
            ""
            "QTableWidget::item {"
            "    background-color: #c2edd3;"      // Background color for items
            "    color: #ffffff;"                  // Text color for items
            "    border: 1px solid #144026;"       // Border color for items
            "}"
            ""
            "QTableWidget::item:selected {"
            "    background-color: #2a5e3f;"      // Background color for selected items
            "    color: #ffffff;"                  // Text color for selected items
            "}";
    QString tab_style= "QTableView {"
                      "    background-color: #c2edd3;"  // Background color
                      "    border: 1px solid #144026;"
            "border-width:2px;"// Border color
                      "    gridline-color: #bdc3c7;"
             // Color of gridlines
                      "}"
                      ""
                      "QHeaderView::section {"
                      "    background-color: #144026;"  // Background color of header sections
                      "    color: #ffffff;"              // Text color of header sections
                      "    padding: 4px;"                // Padding in header sections
                      "    border: 1px solid #144026;"   // Border color of header sections
                      "}"
                      ""
                      "QTableView::item {"
                      "    padding: 5px;"                // Padding around table items
                      "    border-bottom: 1px solid #bdc3c7;"  // Border color at the bottom of each item

                      "}"
                      ""
                      "QTableView::item:selected {"
                      "    background-color: #3498db;"  // Background color of selected items
                      "    color: #ffffff;"
                               // Text color of selected items
                      "}";


    QString titleStyleSheet =
        "QLabel {"
        "    qproperty-alignment: AlignCenter;"
        "    background-color: rgba(0, 225, 193, 0.6);"  // Transparent background color for the title
        "    color: #ffffff;"                               // Text color
        "    font-size: 24px;"                              // Font size
        "    padding: 10px;"
        "    border-bottom: 2px solid #ffffff;"
        "    border-radius: 6px"
        // Bottom border for separation
        "}";
 ui->lineEditPlaqueImmatriculation->setStyleSheet(lineEdit_style);
  ui->le_marque->setStyleSheet(lineEdit_style);
   // ui->->(lineEdit_style);ajouter_vo
  ui->ajouter_vo->setStyleSheet(button1_style);
   ui->tabWidget_3->setStyleSheet(tabWidget_style);
ui->le_modele->setStyleSheet(lineEdit_style);

ui->groupBox_6->setStyleSheet(group_box_style);
ui->le_afb->setStyleSheet(lineEdit_style);
ui->le_tarifs->setStyleSheet(lineEdit_style);
ui->le_kilometrage->setStyleSheet(lineEdit_style);
ui->le_plaque_dimmat->setStyleSheet(lineEdit_style);
ui->le_etat->setStyleSheet(lineEdit_style);
ui->cherche->setStyleSheet(lineEdit_style);
ui->lineEdit_8->setStyleSheet(lineEdit_style);
ui->dateTimeEditConfig->setStyleSheet(lineEdit_style);
ui->lineEditPlaqueImmatriculation->setStyleSheet(lineEdit_style);
ui->groupBox_7->setStyleSheet(group_box_style);
ui->groupBox_8->setStyleSheet(group_box_style);
ui->chercher_sara->setStyleSheet(button1_style);
ui->supp_sara->setStyleSheet(button1_style);
ui->modifier_2->setStyleSheet(button1_style);
ui->stat_sarah->setStyleSheet(button1_style);
ui->pdf_sara->setStyleSheet(button1_style);
ui->kilometrage->setStyleSheet(button1_style);
ui->tarifs->setStyleSheet(button1_style);
ui->pushButton_trianne_2->setStyleSheet(button1_style);
ui->OK->setStyleSheet(button1_style);
ui->pushButton_20->setStyleSheet(button1_style);
ui->qrcode->setStyleSheet(button1_style);
ui->groupBox_9->setStyleSheet(group_box_style);
ui->affichertab->setStyleSheet(tab_style);
ui->pushButton_22->setStyleSheet(button1_style);

}


