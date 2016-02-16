using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Linq;
using System.Globalization;

namespace CMAInterestCalc
{
    public partial class Form1 : Form
    {

        XDocument xmlDoc;
        int tMoney = 0;
        int tInterest = 0;

        int yMoney = 0;
        int yInterest = 0;
        CultureInfo korInfo = CultureInfo.GetCultureInfo("ko-KR");


        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            xmlDoc = XDocument.Load("CMAInterestCalc.xml");

            yMoney = int.Parse(xmlDoc.Element("CMA_INTEREST_CALC").Element("LastMoney").Value);
            yInterest = int.Parse(xmlDoc.Element("CMA_INTEREST_CALC").Element("LastInterest").Value);

            lblYesterdayMoney.Text = "전일금액 : " + string.Format(korInfo, "{0:C}", yMoney);
            lblYesterdayInterest.Text = "전일이자 : " + string.Format(korInfo, "{0:C}", yInterest);
            
        }

        private void btnCalc_Click(object sender, EventArgs e)
        {
            // 계산법 : 금일이자합 = 전일이자 + (금일잔액 - (전일잔액 + 금일입출금액))

            tMoney = int.Parse(tbTodayMoney.Text);
            int plusMoney = int.Parse(tbTodayPlusMoney.Text);

            tInterest = yInterest + (tMoney - (yMoney + plusMoney));
            lblTodayInterest.Text = "금일이자 : " + string.Format(korInfo, "{0:C}", tInterest - yInterest);
            lblTodayInterestPlus.Text = "금일이자합 : " + string.Format(korInfo, "{0:C}", tInterest);
        }

        private void btnXMLUpdate_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("XML을 업데이트 합니다", "XML업데이트", MessageBoxButtons.YesNo) == DialogResult.Yes)
            {
                xmlDoc.Element("CMA_INTEREST_CALC").Element("LastMoney").Value = tMoney.ToString();
                xmlDoc.Element("CMA_INTEREST_CALC").Element("LastInterest").Value = tInterest.ToString();
                xmlDoc.Element("CMA_INTEREST_CALC").Element("WriteDate").Value = string.Format("{0:yyyyMMdd}", DateTime.Now);

                xmlDoc.Save("CMAInterestCalc.xml");

                MessageBox.Show("XML 저장을 완료하였습니다.");
            }
        }        
    }
}
