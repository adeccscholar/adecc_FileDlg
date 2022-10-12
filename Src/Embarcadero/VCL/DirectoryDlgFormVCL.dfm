object frmDirectoryDlgVCL: TfrmDirectoryDlgVCL
  Left = 0
  Top = 0
  Caption = 'frmDirectoryDlgVCL'
  ClientHeight = 921
  ClientWidth = 1110
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -25
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnCreate = FormCreate
  PixelsPerInch = 200
  TextHeight = 35
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1110
    Height = 176
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alTop
    Caption = 'edtPath'
    TabOrder = 0
    DesignSize = (
      1110
      176)
    object lblDrives: TLabel
      Left = 43
      Top = 17
      Width = 96
      Height = 35
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'lblDrives'
    end
    object lblDirectories: TLabel
      Left = 22
      Top = 128
      Width = 147
      Height = 35
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'lblDirectories'
    end
    object lblPath: TLabel
      Left = 43
      Top = 75
      Width = 75
      Height = 35
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'lblPath'
    end
    object cbxDrives: TComboBox
      Left = 204
      Top = 17
      Width = 269
      Height = 43
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Style = csDropDownList
      TabOrder = 0
      OnChange = cbxDrivesChange
    end
    object edtPath: TEdit
      Left = 204
      Top = 72
      Width = 879
      Height = 43
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 1
      Text = 'edtPath'
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 836
    Width = 1110
    Height = 85
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alBottom
    TabOrder = 1
    object btnOk: TButton
      Left = 69
      Top = 12
      Width = 156
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnOk'
      Default = True
      ModalResult = 1
      TabOrder = 0
      OnClick = btnOkClick
    end
    object btnCancel: TButton
      Left = 254
      Top = 12
      Width = 156
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnCancel'
      ModalResult = 2
      TabOrder = 1
      OnClick = btnCancelClick
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 176
    Width = 1110
    Height = 660
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alClient
    Caption = 'edtPath'
    TabOrder = 2
    DesignSize = (
      1110
      660)
    object lbDirectories: TListBox
      Left = 20
      Top = 0
      Width = 1068
      Height = 660
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Anchors = [akLeft, akTop, akRight, akBottom]
      ItemHeight = 35
      TabOrder = 0
      OnDblClick = lbDirectoriesDblClick
    end
  end
end
