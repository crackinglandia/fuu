object FormGrepStringsDialog: TFormGrepStringsDialog
  Left = 279
  Top = 106
  Width = 480
  Height = 409
  Caption = 'FormGrepStringsDialog'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object LabelStringSearch: TLabel
    Left = 9
    Top = 311
    Width = 79
    Height = 13
    Caption = 'String to Search:'
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 363
    Width = 472
    Height = 19
    Panels = <
      item
        Width = 106
      end
      item
        Width = 106
      end
      item
        Width = 106
      end
      item
        Width = 50
      end>
    SimplePanel = False
    OnDrawPanel = StatusBarDrawPanel
  end
  object TabControl: TTabControl
    Left = 0
    Top = 0
    Width = 472
    Height = 297
    Align = alTop
    TabOrder = 1
    Tabs.Strings = (
      'ASCII'
      'ASCIIZ'
      'UNICODE')
    TabIndex = 0
    OnChange = TabControlChange
    object StringGrid: TStringGrid
      Left = 4
      Top = 24
      Width = 464
      Height = 269
      Align = alClient
      ColCount = 3
      DefaultColWidth = 50
      DefaultRowHeight = 18
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      ParentFont = False
      ParentShowHint = False
      PopupMenu = PopupMenu
      ShowHint = True
      TabOrder = 0
      OnMouseMove = StringGridMouseMove
      ColWidths = (
        50
        79
        310)
    end
    object ProgressBar1: TProgressBar
      Left = 269
      Top = 135
      Width = 150
      Height = 16
      Min = 0
      Max = 100
      Position = 40
      TabOrder = 1
      Visible = False
    end
  end
  object CheckBHexAdress: TCheckBox
    Left = 128
    Top = 200
    Width = 97
    Height = 17
    Caption = 'Use Hex Adress'
    TabOrder = 2
    OnClick = CheckBHexAdressClick
  end
  object CheckBContainString: TCheckBox
    Left = 24
    Top = 200
    Width = 97
    Height = 17
    Caption = 'Contain string'
    Enabled = False
    TabOrder = 3
    OnClick = CheckBContainStringClick
  end
  object EdStringSearch: TEdit
    Left = 9
    Top = 331
    Width = 320
    Height = 21
    Enabled = False
    TabOrder = 4
    OnChange = EdStringSearchChange
  end
  object CheckListBOptions: TCheckListBox
    Left = 337
    Top = 302
    Width = 129
    Height = 49
    ItemHeight = 13
    Items.Strings = (
      'Contains The String'
      'Case Sensitive'
      'Use Hex Adress')
    TabOrder = 5
  end
  object OpenDialog: TOpenDialog
    Filter = 'Todos los archivos (*.*)|*.*'
    Left = 400
    Top = 65528
  end
  object PopupMenu: TPopupMenu
    Left = 424
    Top = 160
    object CopyText1: TMenuItem
      Caption = 'Copy Text'
      OnClick = CopyText1Click
    end
    object CopyAddress1: TMenuItem
      Caption = 'Copy Address'
      OnClick = CopyAddress1Click
    end
    object CopyString1: TMenuItem
      Caption = 'Copy String'
      OnClick = CopyString1Click
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object SaveToFile1: TMenuItem
      Caption = 'Save To File'
      OnClick = SaveToFile1Click
    end
    object SaveAllToFile1: TMenuItem
      Caption = 'Save All To File'
      OnClick = SaveAllToFile1Click
    end
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'txt'
    Filter = 'All Files (*.*)|*.*|Text Files (*.txt)|*.txt'
    Left = 352
    Top = 72
  end
end
