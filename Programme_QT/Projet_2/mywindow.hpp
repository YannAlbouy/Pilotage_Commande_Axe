#include <QGridLayout>
#include <QDesktopWidget>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QTextStream>
#include <QFileDialog>

class MyWindow : public QWidget
{
	Q_OBJECT
	private:		
		/*----Pour la saisie du texte----*/
		QLabel *monLabel;
		QLabel* lbl;
		QLabel* lbl2;
		QPixmap pix;
		int tabFin[0][2];
		int myWidth = 0;
		int myHeight = 0;
		QImage image;
		QImage imgTest;
		
	public:
		MyWindow(){
		
			/*----Parametres de ma window----*/
			this->setWindowTitle("ConvertionDessin");
			this->resize(640,360);
			
			/*----Création de mes boutons----*/
			QPushButton* pushOpen = new QPushButton("Ouvrir");
			pushOpen->setStyleSheet("background-color: green;");	
			
			QPushButton* pushSave = new QPushButton("Enregistrer");
			pushSave->setStyleSheet("background-color: green;");
			
			QPushButton* pushConvertir = new QPushButton();
			QPixmap pixSave("./Icones/convertir.png");
			QIcon iconeSave(pixSave);
			pushConvertir->setIcon(iconeSave);
					
			/*----Ma boite principale ou il y aura tout----*/
			QGridLayout *maGrille = new QGridLayout();
						
			lbl = new QLabel(this);
			lbl->setAlignment(Qt::AlignCenter);
			lbl2 = new QLabel(this);
			lbl2->setAlignment(Qt::AlignCenter);

			maGrille->addWidget(lbl,0,0);
			maGrille->addWidget(pushConvertir,0,1);
			maGrille->addWidget(lbl2,0,2);
			maGrille->addWidget(pushOpen,1,1);

			
			/*----CONNECT----*/
			connect(pushOpen,SIGNAL(clicked()),this,SLOT(open()));
			connect(pushConvertir,SIGNAL(clicked()),this,SLOT(convertir()));
			
			/*----AFFICHAGE DE MA GRILLE----*/
			this->setLayout(maGrille);
		}
	public slots:
			void open()
			{
				QString filename = QFileDialog::getOpenFileName(this,"Select source file",".","Jpeg files (*.jpg);; Png files (*.png);; All files (*.*)");
				/** to check wether load ok */
				
				if(imgTest.load(filename)&&pix.load(filename)){
					/** scale pixmap to fit in label'size and keep ratio of pixmap */
					//pix = pix.scaled(lbl->size(),Qt::KeepAspectRatio);
					/*----Mise a la taille voulue----*/
					/*----Y doit etre 100 car nb pos moteur----*/
					lbl->setPixmap(QPixmap::fromImage(imgTest).scaled(this->width()/2,this->height()/2));//setPixmap(pix.scaled(this->width()/2,this->height()/2));
					//qDebug()<<"Res : "<<pix;
				}
			
				/*----Recuperation taille image----*/
				myWidth = imgTest.width();
				qDebug()<<"Width : "<<myWidth;
				myHeight = imgTest.height();
				qDebug()<<"Height : "<<myHeight;
				return;
			}
			void convertir()
			{
				QString nomFic = QFileDialog::getSaveFileName(this, tr("Sauvegarde des coordonnées"), "", tr("Sauvegarde coordonnées (*.txt)"));
				QFile fichier(nomFic);
				if (fichier.open(QIODevice::ReadWrite)) 
				{
					QTextStream stream(&fichier);
					stream <<"[";
					
					int *matrix = new int [myWidth*myHeight];			
					for(int j = 0; j < myHeight; j++)
					{
						for(int i = 0; i < myWidth; i++)
						{
							/*----CONTOUR NOIR----*/
							if(qGray(imgTest.pixel(i,j)) == 0 || qGray(imgTest.pixel(i,j))<236)
							{
								matrix[j*myWidth+i] = qGray(imgTest.pixel(i,j));
								
							}
							else if(qGray(imgTest.pixel(i,j)) >= 236 || qGray(imgTest.pixel(i,j)) <= 254){
								matrix[j*myWidth+i] = '#FFFFFF';
							}
							//else{
								//matrix[j*myWidth+i] = 0;
							//}
						}
					}
					/*----Remettre en image----*/
					QImage img1(myWidth,myHeight, QImage::Format_RGB16);
					for(int j = 0; j < myHeight; j++)
					{
						for(int i = 0; i < myWidth; i++)
						{
							img1.setPixel(i,j,matrix[j*myWidth+i]);
						}
					}
					lbl2->setPixmap(QPixmap::fromImage(img1).scaled(this->width()/2,this->height()/2));
					
					
					/*----UTILISATION PIXMAP RECUPERATION COORDONNEES----*/
					int w = 200;
					int h = 100;
				// set a scaled pixmap to a w x h window keeping its aspect ratio 
					pix = pix.scaled(w,h,Qt::KeepAspectRatio);
					//lbl2->setPixmap(pix.scaled(this->width()/2,this->height()/2));
					
					QImage imageMod = pix.toImage();
					
					tabFin[pix.width()][2];
					int first = -1;
					int laSuite = -1;
					int premier = 0;
					/*----Largeur----*/
					qDebug()<<"Width : "<<pix.width()<<" height : "<<pix.height();
					for(int j = 0; j < pix.width() ; j++)
					{
						/*----Hauteur----*/
						for(int i = 0; i < pix.height(); i++)
						{
							/*----Récupération couleur----*/
							QRgb pixColor = imageMod.pixel(j,i);
							/*----QUAND LE PIXEL EST NOIR----*/
							if(qRed(pixColor) == 0 && qGreen(pixColor) == 0 && qBlue(pixColor) == 0)
							{
							     if(first == -1)
							     {
								premier = i;
								//qDebug()<<"First : "<<i <<" En coord : "<<j;
								first = 0;
							     }
							     else if(first == 0 && laSuite < i)
							     {
							     	laSuite = i;
							     }
		               			}
		               			/*----Si on a pas de pixel noir----*/
						}
						if(laSuite == -1)
						{
							laSuite = 0;
							premier = 0;
						}
						stream<<premier<<","<<laSuite<<",";
						first = -1;
						laSuite = -1;
					}
				stream <<"-1]";
				fichier.flush();
				fichier.close();
				}
			}
			
};
