namespace CMAInterestCalc
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.lblYesterdayMoney = new System.Windows.Forms.Label();
            this.lblYesterdayInterest = new System.Windows.Forms.Label();
            this.lblTodayInterestPlus = new System.Windows.Forms.Label();
            this.tbTodayMoney = new System.Windows.Forms.TextBox();
            this.tbTodayPlusMoney = new System.Windows.Forms.TextBox();
            this.btnCalc = new System.Windows.Forms.Button();
            this.btnXMLUpdate = new System.Windows.Forms.Button();
            this.lblTodayInterest = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "금일잔액";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(10, 200);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(405, 12);
            this.label3.TabIndex = 0;
            this.label3.Text = "계산법 : 금일이자합 = 전일이자 + (금일잔액 - (전일잔액 + 금일입출금액))";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 55);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(163, 12);
            this.label4.TabIndex = 3;
            this.label4.Text = "금일입출금액(출금시예 -500)";
            // 
            // lblYesterdayMoney
            // 
            this.lblYesterdayMoney.AutoSize = true;
            this.lblYesterdayMoney.Location = new System.Drawing.Point(12, 96);
            this.lblYesterdayMoney.Name = "lblYesterdayMoney";
            this.lblYesterdayMoney.Size = new System.Drawing.Size(61, 12);
            this.lblYesterdayMoney.TabIndex = 4;
            this.lblYesterdayMoney.Text = "전일잔액 :";
            // 
            // lblYesterdayInterest
            // 
            this.lblYesterdayInterest.AutoSize = true;
            this.lblYesterdayInterest.Location = new System.Drawing.Point(12, 120);
            this.lblYesterdayInterest.Name = "lblYesterdayInterest";
            this.lblYesterdayInterest.Size = new System.Drawing.Size(61, 12);
            this.lblYesterdayInterest.TabIndex = 5;
            this.lblYesterdayInterest.Text = "전일이자 :";
            // 
            // lblTodayInterestPlus
            // 
            this.lblTodayInterestPlus.AutoSize = true;
            this.lblTodayInterestPlus.Location = new System.Drawing.Point(12, 172);
            this.lblTodayInterestPlus.Name = "lblTodayInterestPlus";
            this.lblTodayInterestPlus.Size = new System.Drawing.Size(77, 12);
            this.lblTodayInterestPlus.TabIndex = 6;
            this.lblTodayInterestPlus.Text = "금일이자합 : ";
            // 
            // tbTodayMoney
            // 
            this.tbTodayMoney.Location = new System.Drawing.Point(222, 15);
            this.tbTodayMoney.Name = "tbTodayMoney";
            this.tbTodayMoney.Size = new System.Drawing.Size(193, 21);
            this.tbTodayMoney.TabIndex = 7;
            this.tbTodayMoney.Text = "0";
            // 
            // tbTodayPlusMoney
            // 
            this.tbTodayPlusMoney.Location = new System.Drawing.Point(222, 46);
            this.tbTodayPlusMoney.Name = "tbTodayPlusMoney";
            this.tbTodayPlusMoney.Size = new System.Drawing.Size(193, 21);
            this.tbTodayPlusMoney.TabIndex = 8;
            this.tbTodayPlusMoney.Text = "0";
            // 
            // btnCalc
            // 
            this.btnCalc.Location = new System.Drawing.Point(323, 108);
            this.btnCalc.Name = "btnCalc";
            this.btnCalc.Size = new System.Drawing.Size(92, 35);
            this.btnCalc.TabIndex = 10;
            this.btnCalc.Text = "계산";
            this.btnCalc.UseVisualStyleBackColor = true;
            this.btnCalc.Click += new System.EventHandler(this.btnCalc_Click);
            // 
            // btnXMLUpdate
            // 
            this.btnXMLUpdate.Location = new System.Drawing.Point(323, 149);
            this.btnXMLUpdate.Name = "btnXMLUpdate";
            this.btnXMLUpdate.Size = new System.Drawing.Size(92, 35);
            this.btnXMLUpdate.TabIndex = 11;
            this.btnXMLUpdate.Text = "XML업데이트";
            this.btnXMLUpdate.UseVisualStyleBackColor = true;
            this.btnXMLUpdate.Click += new System.EventHandler(this.btnXMLUpdate_Click);
            // 
            // lblTodayInterest
            // 
            this.lblTodayInterest.AutoSize = true;
            this.lblTodayInterest.Location = new System.Drawing.Point(12, 146);
            this.lblTodayInterest.Name = "lblTodayInterest";
            this.lblTodayInterest.Size = new System.Drawing.Size(61, 12);
            this.lblTodayInterest.TabIndex = 12;
            this.lblTodayInterest.Text = "금일이자 :";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(428, 239);
            this.Controls.Add(this.lblTodayInterest);
            this.Controls.Add(this.btnXMLUpdate);
            this.Controls.Add(this.btnCalc);
            this.Controls.Add(this.tbTodayPlusMoney);
            this.Controls.Add(this.tbTodayMoney);
            this.Controls.Add(this.lblTodayInterestPlus);
            this.Controls.Add(this.lblYesterdayInterest);
            this.Controls.Add(this.lblYesterdayMoney);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Form1";
            this.Text = "CMA이자정산툴";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label lblYesterdayMoney;
        private System.Windows.Forms.Label lblYesterdayInterest;
        private System.Windows.Forms.Label lblTodayInterestPlus;
        private System.Windows.Forms.TextBox tbTodayMoney;
        private System.Windows.Forms.TextBox tbTodayPlusMoney;
        private System.Windows.Forms.Button btnCalc;
        private System.Windows.Forms.Button btnXMLUpdate;
        private System.Windows.Forms.Label lblTodayInterest;
    }
}

