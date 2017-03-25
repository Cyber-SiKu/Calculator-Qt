#include "mainwindow.h"

#include <QDebug>
#include <QRegExpValidator>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

	v_box_layout = new QVBoxLayout();
	line_edit_input = new QLineEdit();
	// use regular  expression to limit the input line
	QRegExp limit_input = QRegExp("^(\\d+)((['+','-','*','/'])(\\d+))+$");
	QRegExpValidator *validator = new QRegExpValidator(limit_input, this);
	this->line_edit_input->setValidator(validator);
	this->v_box_layout->addWidget(line_edit_input);

	line_edit_output = new QLineEdit();
	line_edit_output->setReadOnly(true);
	this->v_box_layout->addWidget(line_edit_output);

	// add the operator push button
	h_box_layout = new QHBoxLayout();
	v_box_layout_operator = new QVBoxLayout();
	QString strs[5]{"+", "-", "*", "/", "="};
	push_button_operator = new QPushButton[5];
	for (int i = 0; i < 5; i++) {
		(push_button_operator + i)->setText(strs[i]);
		(push_button_operator + i)->setObjectName(strs[i]);
		connect(push_button_operator + i, SIGNAL(clicked()), this,
			SLOT(pushButtonClicked()));
		v_box_layout_operator->addWidget(push_button_operator + i);
	}

	h_box_layout->addLayout(v_box_layout_operator);

	// add the number push button
	const int MAXSIZE = 10;
	push_button_number = new QPushButton[MAXSIZE]();
	grid_layout = new QGridLayout();
	for (int i = 0; i < MAXSIZE; ++i) {
		// set the number push button
		QString str;
		str.setNum(i);
		(push_button_number + i)->setText(str);
		(push_button_number + i)->setObjectName(str);
		connect(push_button_number + i, SIGNAL(clicked()), this,
			SLOT(pushButtonClicked()));
		grid_layout->addWidget(push_button_number + i, i / 3, i % 3);
	}

	h_box_layout->addLayout(grid_layout);

	v_box_layout->addLayout(h_box_layout);

	widget = new QWidget();
	widget->setLayout(v_box_layout);
	widget->show();
	setCentralWidget(widget);
}

MainWindow::~MainWindow() {}

void MainWindow::pushButtonClicked() {
	QString object_name = sender()->objectName();
	if (object_name != tr("=")) {
		this->line_edit_input->insert(object_name);
	} else {
		QString formula  = this->line_edit_input->text();
		if (formula == tr("the answer is:")) {
			// the answer of all
			this->line_edit_output->setText(tr("42"));
		}else{
			QString formula = line_edit_input->text();
			this->line_edit_input->setText(tr(""));
			QStringList operand = formula.split(QRegExp("['+','-','*','/']"));
			QStringList opt = formula.split(QRegExp("[0,1,2,3,4,5,6,7,8,9]"),QString::SkipEmptyParts);
			int result = operand[0].toInt();
			for(int i = 1,j = 0;i < operand.length();++i,++j){
				if (opt[j] == "+") {
					result+=operand[i].toInt();
				}else if(opt[j] == "-"){
					result-=operand[i].toInt();
				}else if(opt[j] == "*"){
					result*=operand[i].toInt();
				} else if(opt[j] == "/"){
					result/=operand[i].toInt();
				}else{

				}
			}
			QString str;
			str.setNum(result);
			this->line_edit_output->setText(str);
		}
	}
}
