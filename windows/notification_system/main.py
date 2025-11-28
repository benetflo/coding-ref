from windows_toasts import Toast, WindowsToaster, AudioSource, ToastAudio

toaster = WindowsToaster('!!! YOU WON CONGRATULATIONS !!!')

newToast = Toast()
newToast.text_fields = ['Hello there! You just won a thousand dollars! Click me to claim it!']
newToast.launch_action = 'https://www.youtube.com/watch?v=XfELJU1mRMg'
newToast.audio = ToastAudio(AudioSource.IM, looping=True)

# send notification
toaster.show_toast(newToast)