object frmFileShowVCL: TfrmFileShowVCL
  Left = 162
  Top = 163
  Caption = 'frmFileShowVCL'
  ClientHeight = 1441
  ClientWidth = 2495
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -25
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  PixelsPerInch = 200
  TextHeight = 35
  object memFile: TMemo
    Left = 0
    Top = 0
    Width = 2495
    Height = 1355
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alClient
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -29
    Font.Name = 'Courier New'
    Font.Style = []
    Lines.Strings = (
      'memFile')
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 0
    ExplicitWidth = 1307
    ExplicitHeight = 843
  end
  object pnlCtrl: TPanel
    Left = 0
    Top = 1355
    Width = 2495
    Height = 86
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alBottom
    TabOrder = 1
    ExplicitTop = 843
    ExplicitWidth = 1307
    object btnOk: TButton
      Left = 34
      Top = 12
      Width = 156
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnOk'
      Default = True
      ModalResult = 8
      TabOrder = 0
    end
  end
end
