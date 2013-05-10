#include "Qtviewer.h"

Qtviewer::Qtviewer(QWidget *parent): QWidget(parent)
{
    QHBoxLayout *layout_button = new QHBoxLayout;
    QVBoxLayout *layout_list = new QVBoxLayout;    
    QVBoxLayout *layout_img_button = new QVBoxLayout;
    QHBoxLayout *layout_main = new QHBoxLayout;
   
    
    QLabel *label_sel_scan = new QLabel("Select Chapter :");
    QLabel *label_sel_dir = new QLabel("Select Dir :");
    QLabel *label_sel_page = new QLabel("Select Page :");

    QPushButton *next_page = new QPushButton(tr("&Next"));
    QPushButton *prev_page = new QPushButton(tr("&Prev"));
    QPushButton *first_page = new QPushButton(tr("&First"));
    QPushButton *last_page = new QPushButton(tr("&Last"));
   
    label_cur_scan = new QLabel("");
    ql_num_scan = new QLineEdit;
    list_dir_page = new QListWidget;
    list_dir_scan = new QListWidget;
    image_current = new QLabel("");
    name_scan = "";
    path_scan = "";

    num_page = new LineNumPage;
    
    connect(next_page, SIGNAL(clicked()), this, SLOT(btn_next_page()));
    connect(prev_page, SIGNAL(clicked()), this, SLOT(btn_prev_page()));
    connect(first_page, SIGNAL(clicked()), this, SLOT(btn_first_page()));
    connect(last_page, SIGNAL(clicked()), this, SLOT(btn_last_page()));    
    connect(num_page,SIGNAL(returnPressed()),this,SLOT(txt_go_page()));
    connect(list_dir_scan,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(list_go_scan()));
    connect(list_dir_page,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(list_go_page()));

    layout_button->addWidget(first_page);   
    layout_button->addWidget(prev_page);
    layout_button->addWidget(num_page);
    layout_button->addWidget(next_page);   
    layout_button->addWidget(last_page);

    image_current->setAlignment(Qt::AlignCenter);

    layout_list->addWidget(label_cur_scan);
    layout_list->addWidget(label_sel_scan);
    layout_list->addWidget(ql_num_scan);
    layout_list->addWidget(label_sel_dir);
    layout_list->addWidget(list_dir_scan);
    layout_list->addWidget(label_sel_page);
    layout_list->addWidget(list_dir_page);

    layout_img_button->addWidget(image_current);
    layout_img_button->addItem(layout_button);

    layout_main->addLayout(layout_list);
    layout_main->addLayout(layout_img_button,1);
    setLayout(layout_main);  
   
}

void Qtviewer::setScan(string name,int num)
{
    if(Easylast::is_dir(PATH_SCANS+name+'/'+Easylast::itos(num)+'/'))
    {
	name_scan = name;
	num_scan = num;
	curr_page = 0;
	path_scan = PATH_SCANS+name+'/'+Easylast::itos(num)+'/';

	pages_scan = Easylast::list_dir(path_scan);
	
	nb_page = pages_scan.size()-1;
	
	clear_lists();
	fill_lists();
	display_image_curr();
    }
}

void Qtviewer::setQSummary(QSummaryManga *sum)
{
    SummManga = sum;
}

void  Qtviewer::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);
    cout << event->key()<<endl;
    if(event->key() == 70)
    {
	image_current->showFullScreen();
	cout << "full"<<endl;
    }
    if(event->key() == 74)
	btn_prev_page();

    if(event->key() == 77)
	btn_next_page();
}


void Qtviewer::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    
    height_for_img =  image_current->height();
    width_for_img =  image_current->width();
    
    if( name_scan != "")
	display_image_curr();
}
	
void Qtviewer::btn_next_page()
{
    if (curr_page < nb_page)
    {
	curr_page++;
	display_image_curr();
    }
    else
    {
	emit nextScan(name_scan,num_scan);
    }

}

void Qtviewer::btn_prev_page()
{
    if(curr_page > 0)
    {
	curr_page--;
	display_image_curr();
    }
}

void Qtviewer::btn_first_page()
{
    curr_page = 0;
    display_image_curr();
}

void Qtviewer::btn_last_page()
{
    curr_page = nb_page;
    display_image_curr();
}

void Qtviewer::txt_go_page()
{
    QString p = num_page->text();
    string s = p.toStdString();

    curr_page = atoi(s.c_str())-1;
    display_image_curr();
}

void Qtviewer::list_go_scan()
{
    num_scan = Easylast::qstoi(list_dir_scan->currentItem()->text());
    curr_page = 0;
    path_scan = PATH_SCANS+name_scan+'/'+Easylast::itos(num_scan)+'/';
    
    pages_scan = Easylast::list_dir(path_scan);
    
    nb_page = pages_scan.size()-1;
    display_image_curr();
}

void Qtviewer::list_go_page()
{
    curr_page = list_dir_page->currentRow();
    display_image_curr();
}

void Qtviewer::clear_lists()
{ 
    list_dir_scan->clear();
    list_dir_page->clear();
}

void Qtviewer::fill_list_page()
{
    for(vector<string>::iterator it = pages_scan.begin();it != pages_scan.end();++it)
	list_dir_page->addItem(Easylast::stoqs(*it));

    list_dir_page->sortItems();
}

void Qtviewer::fill_lists()
{
    vector<string> list_chaps = Easylast::list_dir(PATH_SCANS+name_scan);

    for(vector<string>::iterator it = list_chaps.begin();it != list_chaps.end();++it)
	list_dir_scan->addItem(Easylast::stoqs(*it));    

    list_dir_scan->sortItems(Qt::DescendingOrder);
    
    fill_list_page();
}

void Qtviewer::display_image(const string & path_img)
{
    QString qs = path_img.c_str();
    QPixmap img = QPixmap(qs);
    QPixmap scaled_img;

    scaled_img = img.scaledToHeight(height_for_img,Qt::SmoothTransformation);
    if(scaled_img.width() > width_for_img)
	scaled_img = img.scaledToWidth(width_for_img,Qt::SmoothTransformation);
    image_current->setPixmap(scaled_img);  
}

void Qtviewer::display_image_curr()
{
    string path_img = path_scan+'/'+pages_scan[curr_page];
    cout << path_img << endl;
    display_image(path_img);
    update_label();
}

void Qtviewer::update_label()
{
    label_cur_scan->setText(Easylast::stoqs(name_scan+" "+Easylast::itos(num_scan)));
    num_page->setText(Easylast::itoqs(curr_page+1));
}
