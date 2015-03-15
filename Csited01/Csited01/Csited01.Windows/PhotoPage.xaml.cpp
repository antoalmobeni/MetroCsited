//
// PhotoPage.xaml.cpp
// Implementation of the PhotoPage class
//

#include "pch.h"
#include "PhotoPage.xaml.h"

using namespace Csited01;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Basic Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234237

PhotoPage::PhotoPage()
{
	InitializeComponent();
	SetValue(_defaultViewModelProperty, ref new Map<String^,Object^>(std::less<String^>()));
	auto navigationHelper = ref new Common::NavigationHelper(this);
	SetValue(_navigationHelperProperty, navigationHelper);
	navigationHelper->LoadState += ref new Common::LoadStateEventHandler(this, &PhotoPage::LoadState);
	navigationHelper->SaveState += ref new Common::SaveStateEventHandler(this, &PhotoPage::SaveState);
}

DependencyProperty^ PhotoPage::_defaultViewModelProperty =
	DependencyProperty::Register("DefaultViewModel",
		TypeName(IObservableMap<String^,Object^>::typeid), TypeName(PhotoPage::typeid), nullptr);

/// <summary>
/// used as a trivial view model.
/// </summary>
IObservableMap<String^, Object^>^ PhotoPage::DefaultViewModel::get()
{
	return safe_cast<IObservableMap<String^, Object^>^>(GetValue(_defaultViewModelProperty));
}

DependencyProperty^ PhotoPage::_navigationHelperProperty =
	DependencyProperty::Register("NavigationHelper",
		TypeName(Common::NavigationHelper::typeid), TypeName(PhotoPage::typeid), nullptr);

/// <summary>
/// Gets an implementation of <see cref="NavigationHelper"/> designed to be
/// used as a trivial view model.
/// </summary>
Common::NavigationHelper^ PhotoPage::NavigationHelper::get()
{
	return safe_cast<Common::NavigationHelper^>(GetValue(_navigationHelperProperty));
}

#pragma region Navigation support

/// The methods provided in this section are simply used to allow
/// NavigationHelper to respond to the page's navigation methods.
/// 
/// Page specific logic should be placed in event handlers for the  
/// <see cref="NavigationHelper::LoadState"/>
/// and <see cref="NavigationHelper::SaveState"/>.
/// The navigation parameter is available in the LoadState method 
/// in addition to page state preserved during an earlier session.

void PhotoPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedTo(e);
}

void PhotoPage::OnNavigatedFrom(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedFrom(e);
}

#pragma endregion

/// <summary>
/// Populates the page with content passed during navigation. Any saved state is also
/// provided when recreating a page from a prior session.
/// </summary>
/// <param name="sender">
/// The source of the event; typically <see cref="NavigationHelper"/>
/// </param>
/// <param name="e">Event data that provides both the navigation parameter passed to
/// <see cref="Frame.Navigate(Type, Object)"/> when this page was initially requested and
/// a dictionary of state preserved by this page during an earlier
/// session. The state will be null the first time a page is visited.</param>
void PhotoPage::LoadState(Object^ sender, Common::LoadStateEventArgs^ e)
{
	(void) sender;	// Unused parameter
	(void) e;	// Unused parameter
}

/// <summary>
/// Preserves state associated with this page in case the application is suspended or the
/// page is discarded from the navigation cache.  Values must conform to the serialization
/// requirements of <see cref="SuspensionManager::SessionState"/>.
/// </summary>
/// <param name="sender">The source of the event; typically <see cref="NavigationHelper"/></param>
/// <param name="e">Event data that provides an empty dictionary to be populated with
/// serializable state.</param>
void PhotoPage::SaveState(Object^ sender, Common::SaveStateEventArgs^ e){
	(void) sender;	// Unused parameter
	(void) e; // Unused parameter
}


void Csited01::PhotoPage::pageRoot_SizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ e)
{
	if (e->NewSize.Height / e->NewSize.Width >= 1)
	{
		VisualStateManager::GoToState(this, "Portrait", true);
	}
	else
	{
		VisualStateManager::GoToState(this, "Landscape", true);
	}

}
