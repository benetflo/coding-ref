from win10toast import ToastNotifier

toaster = ToastNotifier()

toaster.show_toast("You got mail!",
                   "Contents of mail...",
                   icon_path="custom.ico",
                   duration=10)