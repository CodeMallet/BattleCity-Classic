#include "CAdminEdit.h"

void *CAdminEditPointer;

int CALLBACK AdminEditDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	CGame *p = (CGame *)CAdminEditPointer;
    switch(Message)
    {
        case WM_INITDIALOG:
			p->AdminEdit->hWnd = hwnd;
			break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
				case IDGET:
				{
					GetDlgItemText(hwnd, IDUSER, p->AdminEdit->user, 15);
					sCMAdminEditRequest AdminEditRequest;
					strcpy(AdminEditRequest.User, p->AdminEdit->user);
					p->Winsock->SendData(cmAdminEditRequest, (char *)&AdminEditRequest, sizeof(AdminEditRequest));
				}
				break;
				case IDOK:
				{
					GetDlgItemText(hwnd, IDUSER, p->AdminEdit->user, 15);
					GetDlgItemText(hwnd, IDPASS, p->AdminEdit->pass, 15);
					GetDlgItemText(hwnd, IDFULLNAME, p->AdminEdit->fullname, 20);
					GetDlgItemText(hwnd, IDEMAIL, p->AdminEdit->email, 50);
					GetDlgItemText(hwnd, IDTOWN, p->AdminEdit->town, 15);
					GetDlgItemText(hwnd, IDSTATE, p->AdminEdit->state, 15);

					p->AdminEdit->points = GetDlgItemInt(hwnd, IDPOINTS, NULL, 0);
					p->AdminEdit->monthlypoints = GetDlgItemInt(hwnd, IDMONTHLYPOINTS, NULL, 0);
					p->AdminEdit->orbs = GetDlgItemInt(hwnd, IDORBS, NULL, 0);
					p->AdminEdit->deaths = GetDlgItemInt(hwnd, IDDEATHS, NULL, 0);
					p->AdminEdit->assists = GetDlgItemInt(hwnd, IDASSISTS, NULL, 0);
					p->AdminEdit->tank = GetDlgItemInt(hwnd, IDTANK, NULL, 0);
					p->AdminEdit->tank2 = GetDlgItemInt(hwnd, IDTANK2, NULL, 0);
					p->AdminEdit->tank3 = GetDlgItemInt(hwnd, IDTANK3, NULL, 0);
					p->AdminEdit->tank4 = GetDlgItemInt(hwnd, IDTANK4, NULL, 0);
					p->AdminEdit->admin = IsDlgButtonChecked(hwnd, IDC_ADMIN);
					p->AdminEdit->member = IsDlgButtonChecked(hwnd, IDC_MEMBER);
					p->AdminEdit->rentalcity = GetDlgItemInt(hwnd, IDRENTAL, NULL, 0);
					p->AdminEdit->red = GetDlgItemInt(hwnd, IDRED, NULL, 0);
					p->AdminEdit->green = GetDlgItemInt(hwnd, IDGREEN, NULL, 0);
					p->AdminEdit->blue = GetDlgItemInt(hwnd, IDBLUE, NULL, 0);
					if (IsDlgButtonChecked(hwnd, IDC_RAINBOW))
					{
						p->AdminEdit->red = 255;
						p->AdminEdit->green = 255;
						p->AdminEdit->blue = 255;
					}

					sCMAdminEdit AdminEdit;

					strcpy(AdminEdit.User, p->AdminEdit->user);
					strcpy(AdminEdit.Pass, p->AdminEdit->pass);
					strcpy(AdminEdit.FullName, p->AdminEdit->fullname);
					strcpy(AdminEdit.Email, p->AdminEdit->email);
					strcpy(AdminEdit.Town, p->AdminEdit->town);
					strcpy(AdminEdit.State, p->AdminEdit->state);
					
					AdminEdit.Points = p->AdminEdit->points;
					AdminEdit.MonthlyPoints = p->AdminEdit->monthlypoints;
					AdminEdit.Orbs = p->AdminEdit->orbs;
					AdminEdit.Deaths = p->AdminEdit->deaths;
					AdminEdit.Assists = p->AdminEdit->assists;
					AdminEdit.Tank = p->AdminEdit->tank;
					AdminEdit.Tank2 = p->AdminEdit->tank2;
					AdminEdit.Tank3 = p->AdminEdit->tank3;
					AdminEdit.Tank4 = p->AdminEdit->tank4;
					AdminEdit.IsAdmin = p->AdminEdit->admin;
					AdminEdit.Member = p->AdminEdit->member;
					AdminEdit.Red = p->AdminEdit->red;
					AdminEdit.Green = p->AdminEdit->green;
					AdminEdit.Blue = p->AdminEdit->blue;
					AdminEdit.RentalCity = p->AdminEdit->rentalcity;

					p->Winsock->SendData(cmAdminEdit, (char *)&AdminEdit, sizeof(AdminEdit));
				}
				break;
				case IDCANCEL:
				{
					p->AdminEdit->IsOpen = 0;
					p->Dialog->StartDialog = 0;
					EndDialog(hwnd, IDCANCEL);
				}
				break;
            }
			break;
        default:
            return 0;
			break;
    }
    return 1;
}

CAdminEdit::CAdminEdit(CGame *game)
{
	p = game;
	CAdminEditPointer = game;

	IsOpen = 0;
}

CAdminEdit::~CAdminEdit()
{

}

void CAdminEdit::ShowAdminEditDlg()
{
	p->Dialog->StartDialog = ID_EDITACCOUNT;
	p->Dialog->DialogProcessor = &AdminEditDlgProc;
	IsOpen = 1;
}